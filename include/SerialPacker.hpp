// -*- coding:utf-8-unix -*-
/*!
  @file   SerialPacker.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Fri Nov 20 20:30:55 2020
  @version 1.0a

  @brief  Pack Packets for Serial Connections

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef SERIALPACKER_H
#define SERIALPACKER_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include "wxcommon.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {


// Class //////////////////////////////////////////////////////////////////////
class SerialPacker {
private:

public:
  SerialPacker(void);
  ~SerialPacker(void);
  void init(void);
  result_e pack(uint8_t* srcBuffer, const uint8_t srcLength, uint8_t* destBuffer);
};

}

#endif
