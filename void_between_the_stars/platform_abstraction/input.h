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
    kNone = 0,
    kLeftMouse = 1,
    kMiddleMouse = 2,
    kRightMouse = 3,
    kUpArrow = 4,
    kDownArrow = 5,
    kLeftArrow = 6,
    kRightArrow = 7,
    kBackspace = 8,
    kShift = 9,
    kControl = 10,
    kAlt = 11,
    kEsc = 12,
    kReturn = 13,
    kCount
  };
  
  Action action;
  char32_t key;
  int mouse_x;
  int mouse_y;
  
  Input(Action in_action, char32_t in_key, int in_mouse_x, int in_mouse_y)
      : action(in_action)
      , key(in_key)
      , mouse_x(in_mouse_x)
      , mouse_y(in_mouse_y) {
  }
};

#endif //VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__INPUT_H
