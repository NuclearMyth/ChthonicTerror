//
//  main_window.cpp
//
//  Win32 platform abstraction layer of the Void Between The Stars Engine.
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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>
#include "../input.h"

#include <GL/gl.h>

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

HWND h_window = 0;
HDC hdc = 0;
HGLRC hglrc = 0;

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_KEYDOWN:
    //keyDownCount[wParam & 0xff]++;
    return 0;
  case WM_KEYUP:
    //keyUpCount[wParam & 0xff]++;
    return 0;
  case WM_TIMER:
    return 0;
  case WM_PAINT:
    ValidateRect(h_window, nullptr);
    return 0;
  case WM_MOUSEMOVE:
    //OnMouseMove(lParam);
    return 0;
  case WM_RBUTTONDOWN:
    //OnRButtonDown(lParam);
    return 0;
  case WM_RBUTTONUP:
    //OnRButtonUp(lParam);
    return 0;
  case WM_LBUTTONDOWN:
    //OnLButtonDown(lParam);
    return 0;
  case WM_LBUTTONUP:
    //OnLButtonUp(lParam);
    return 0;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CreateMainWindow() {
  char *window_class_name = "Void Between The Stars";

  FreeConsole();

  HINSTANCE h_instance = GetModuleHandle(NULL);
 
  WNDCLASSEX wc = { 0 };
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = WindowProcedure;
  wc.hInstance = h_instance;
  wc.lpszClassName = window_class_name;
  RegisterClassEx(&wc);

  DWORD window_style = WS_CAPTION | WS_SYSMENU | WS_MAXIMIZE;

  h_window = CreateWindowEx(NULL, window_class_name, window_class_name, window_style, 0, 0,
    GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, h_instance, NULL);

  ShowWindow(h_window, SW_SHOW);
  UpdateWindow(h_window);

  static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0/*16*/, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0};
  hdc = GetDC(h_window);
  GLuint pixel_format = ChoosePixelFormat(hdc, &pfd);
  if (pixel_format == 0) {
    MessageBox(h_window, "ChoosePixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
    ExitProcess(1);
  }

  if (!SetPixelFormat(hdc, pixel_format, &pfd)) {
    MessageBox(h_window, "SetPixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
    ExitProcess(1);
  }

  hglrc = wglCreateContext(hdc);
  if (hglrc == 0) {
    MessageBox(h_window, "wglCreateContext failed.", "Error", MB_ICONERROR | MB_OK);
    ExitProcess(1);
  }

  if (!wglMakeCurrent(hdc, hglrc)) {
    MessageBox(h_window, "wglMakeCurrent failed.", "Error", MB_ICONERROR | MB_OK);
    ExitProcess(1);
  }
}

extern void GetMainWindowDimensions(int *out_width, int *out_height) {
  RECT rect;
  GetClientRect(h_window, &rect);
  *out_width = rect.right - rect.left;
  *out_height = rect.bottom - rect.top;
}

void GetInput(std::vector<Input> *out_input) {
  MSG msg;
  while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {
    if (msg.message == WM_QUIT) {
      wglMakeCurrent(NULL, NULL);  
      wglDeleteContext(hglrc);
      ReleaseDC(h_window, hdc);

      ExitProcess(0);
      return;
    }
    if (GetMessage(&msg, NULL, 0, 0)) {
      DispatchMessage(&msg);
      break;
    } else {
      break;
    }
  }
}

void GlSwap() {
  //HDC hdc = GetDC(h_window);
  SwapBuffers(hdc);
  //ReleaseDC(h_window, hdc);
}
