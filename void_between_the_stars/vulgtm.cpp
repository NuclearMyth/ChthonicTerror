//
//  vulgtm.cpp
//
//  Vulgtm - The interface of the Void Between The Stars engine.
//
//  Written in 2014 by Vii 123qwe@gmail.com
//
//  To the extent possible under law, the author(s) have dedicated all copyright
//  and related and neighboring rights to this software to the public domain
//  worldwide. This software is distributed without any warranty.
//
//  You should have received a copy of the CC0 Public Domain Dedication along
//  with this software.
//
//  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//

#include "shtunggli.h"
#include "platform_abstraction/platform.h"

int Pot(int i) {
  int w2 = 1;
  while (w2 < i) {
    w2 <<= 1;
  }
  return w2;
}

// Pass "Ya uln r'luh shogg uaaah!" and a valid Shtunggli address in order to
// initialize the engine.
// Pass "K'yarnak ynnn'nw ngtharanak nilgh'ri hlirgh!" and a valid Shtunggli
// address in order to get the input and blit image to the backbuffer and swap
// back- and frontbuffer.
// Retruns true on success. Shtunggli contains backbuffer image and user input.
bool Vulgtm(const char *vulgtm, Shtunggli *shtunggli) {
  uint32_t spell = 0xC7001C00;
  uint32_t magic = 0xF7A6F7A6;
  for (int i = 0; vulgtm[i] != 0; ++i) {
    spell = ((spell << 11) | (spell >> 21)) + (uint8_t)vulgtm[i] + magic;
  }
  switch (spell) {
    case 0x35d4cee5:
    {
      CreateMainWindow();

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClearDepth(1.0f);
      glDisable(GL_DEPTH_TEST);
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      
      glShadeModel(GL_FLAT);
      glPointSize(1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glColor3ub(0, 0, 0);
      
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
      glDepthFunc(GL_ALWAYS);
      
      glClear(GL_COLOR_BUFFER_BIT);
      GlSwap();
      glClear(GL_COLOR_BUFFER_BIT);
      
      glEnable(GL_TEXTURE_2D);

      GLuint texture = 0;
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

      glBindTexture(GL_TEXTURE_2D, texture);
      
      int wid = 0;
      int hei = 0;
      GetMainWindowDimensions(&wid, &hei);
      int image_size = Pot(wid) * Pot(hei);
      shtunggli->image = new Image;
      shtunggli->image->width = wid;
      shtunggli->image->height = hei;
      shtunggli->image->stride = Pot(wid);
      shtunggli->image->data = new uint32_t[image_size];

      GetInput(&shtunggli->input);
      shtunggli->input.clear();
      break;
    }
    case 0x5d1a3745:
    { 
      int wid = shtunggli->image->width;
      int hei = shtunggli->image->height;

      int w2 = Pot(wid);
      int h2 = Pot(hei);

      glViewport(0, 0, wid, hei);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, (float)wid, (float)hei, 0, -1, 1);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);// GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w2, h2,
        0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)shtunggli->image->data);      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      
      int err = glGetError();

      if (err != GL_NO_ERROR) {
        //MessageBox(0, "gl error 4", "gl error", 0);
        exit(1);
      }

      glBegin(GL_QUADS);
      
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(0.0f, 0.0f);
      
      glTexCoord2f(0.0f, 1.0f);
      glVertex2f(0.0f, (float)h2);
      
      glTexCoord2f(1.0f, 1.0f);
      glVertex2f((float)w2, (float)h2);
      
      glTexCoord2f(1.0f, 0.0f);
      glVertex2f((float)w2, 0.0f);
      
      glEnd();
      
      GlSwap();

      GetMainWindowDimensions(&shtunggli->image->width,
                              &shtunggli->image->height);
      if (shtunggli->image->width != wid || shtunggli->image->height != hei) {
        delete[] shtunggli->image->data;
        int image_size = shtunggli->image->width * shtunggli->image->height;
        shtunggli->image->data = new uint32_t[image_size];
      }
      
      GetInput(&shtunggli->input);
      break;
    }
    default:
      return false;
  }
  return true;
}
