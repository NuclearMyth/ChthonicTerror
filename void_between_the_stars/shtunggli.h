//
//  shtunggli.h
//
//  Shtunggli - The datastructure used to contact the Void Between The Stars.
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

#ifndef VOID_BETWEEN_THE_STARS__SHTUNGGLI_H
#define VOID_BETWEEN_THE_STARS__SHTUNGGLI_H

#include "platform_abstraction/image.h"
#include "platform_abstraction/input.h"
#include <vector>

struct Shtunggli {
  Image *image;
  std::vector<Input> input;
};

#endif //VOID_BETWEEN_THE_STARS__SHTUNGGLI_H
