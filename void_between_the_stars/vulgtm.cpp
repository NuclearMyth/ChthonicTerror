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
//#include <OpenGL/gl.h>
#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>
#include <GL/gl.h>

#define GL_BGRA 0x80E1

extern void CreateMainWindow();
extern void GetMainWindowDimensions(int *out_width, int *out_height);
extern void GetInput(std::vector<Input> *out_input);
extern void GlSwap();

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
      int image_size = wid * hei;
      shtunggli->image = new Image;
      shtunggli->image->width = wid;
      shtunggli->image->height = hei;
      shtunggli->image->data = new uint32_t[image_size];

      GetInput(&shtunggli->input);
      shtunggli->input.clear();
      break;
    }
    case 0x5d1a3745:
    {
      int wid = shtunggli->image->width;
      int hei = shtunggli->image->height;
      glViewport(0, 0, wid, hei);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
      
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, wid, hei,
        0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)shtunggli->image->data);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      
      glBegin(GL_QUADS);
      
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(0.0f, 0.0f);
      
      glTexCoord2f(0.0f, 1.0f);
      glVertex2f(0.0f, (float)hei - 1.0);
      
      glTexCoord2f(1.0f, 1.0f);
      glVertex2f((float)wid - 1.0f, (float)hei - 1.0f);
      
      glTexCoord2f(1.0f, 0.0f);
      glVertex2f((float)wid - 1.0f, 0.0f);
      
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
