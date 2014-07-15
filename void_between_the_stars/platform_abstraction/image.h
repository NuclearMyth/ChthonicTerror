//
//  image.h
//
//  Image - The representation of the backbuffer of the Void Between The Stars.
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

#ifndef VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__IMAGE_H
#define VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__IMAGE_H

#include <stdint.h>

struct Image {
  uint32_t *data;
  int width;
  int height;
};

#endif //VOID_BETWEEN_THE_STARS__PLATFORM_ABSTRACTION__IMAGE_H
