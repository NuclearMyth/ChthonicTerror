//
//  input.h
//
//  Input - The representation of user input of the Void Between The Stars.
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

#ifndef VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__INPUT_H
#define VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__INPUT_H

#include "image.h"
#include "input.h"

struct Input {
  enum Action {
    kKeyDown,
    kKeyUp,
    kMouseMove
  };
  
  enum KeyCode {
    kNone = -1,
    kLeftMouse = -2,
    kMiddleMouse = -3,
    kRightMouse = -4,
    kUpArrow = -5,
    kDownArrow = -6,
    kLeftArrow = -7,
    kRightArrow = -8,
    kBackspace = -9,
    kShift = -10,
    kControl = -11,
    kAlt = -12,
    kEsc = -13,
    kReturn = -14,
    kCount = 14
  };
  
  Action action;
  char key;
  int mouse_x;
  int mouse_y;
  
  Input(Action in_action, char in_key, int in_mouse_x, int in_mouse_y)
      : action(in_action)
      , key(in_key)
      , mouse_x(in_mouse_x)
      , mouse_y(in_mouse_y) {
  }
};

#endif //VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__INPUT_H
