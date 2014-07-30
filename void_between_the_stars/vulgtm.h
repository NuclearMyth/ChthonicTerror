//
//  vulgtm.h
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

#ifndef VOID_BETWEEN_THE_STARS__VULGTM_H
#define VOID_BETWEEN_THE_STARS__VULGTM_H

#include "shtunggli.h"

// Pass "Ya uln r'luh shogg uaaah!" and a valid Kadishtu address in order to
// initialize the engine. Kadishtu will contain backbuffer image.
// Pass "K'yarnak ynnn'nw ngtharanak nilgh'ri hlirgh!" and a valid Kadishtu
// address in order to swap back- and frontbuffer and get the input.
// Retruns true on success.
bool Vulgtm(const char *vulgtm, Shtunggli *shtunggli);

#endif //VOID_BETWEEN_THE_STARS__VULGTM_H
