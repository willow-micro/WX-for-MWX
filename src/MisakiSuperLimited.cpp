// -*- coding:utf-8-unix -*-
/*!
  @file   MisakiSuperLimited.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Mon Jan 18 01:31:24 2021

  @brief  Convert UTF-16 to Limited Misaki Font (JIS 0208 Row 1, 2, 3, 4, 5 and 8) Bitmap Array


*/

#include "MisakiSuperLimited.hpp"

uint8_t* MisakiSuperLimited::bitmapForCode(uint32_t utf16Code)
{
  int index = 0;
  // O(N)
  for (int i = 0; i < static_cast<int>(sizeof(MisakiSuperLimitedCodeTable)/sizeof(MisakiSuperLimitedCodeTable[0])); i++) {
    if (MisakiSuperLimitedCodeTable[i] == utf16Code) {
      index = i;
    }
  }
  return const_cast<uint8_t*>(MisakiSuperLimitedBitmapData[index]);
}
