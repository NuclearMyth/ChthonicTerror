//
//  platform.h
//
//  Platform - platform abstraction layer of the Void Between The Stars.
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

#ifndef VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__PLATFORM_H
#define VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__PLATFORM_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#ifdef _WIN32
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <GL/gl.h>
#define GL_BGRA 0x80E1
#endif

void CreateMainWindow();
void GetMainWindowDimensions(int *out_width, int *out_height);
void GetInput(std::vector<Input> *out_input);
void GlSwap();

#endif //VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__PLATFORM_H
