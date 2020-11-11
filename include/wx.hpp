/*!
  @file   wx.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 18:55:07 2020

  @brief  Willow eXtension Library Header

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef WX_H
#define WX_H

#include "AQM0802.hpp"
#include "ATP3011.hpp"
#include "FIFO.hpp"
#include "Timekeeper.hpp"


namespace wx {

inline boolean isPullupButtonOn(uint32_t state, uint32_t mask, uint8_t pinNum)
{
  if ((~(mask & 0x80000000) & ~(state & (1UL << pinNum))) == 0xFFFFFFFF) {
    return true;
  }
  return false;
}

}

#endif
