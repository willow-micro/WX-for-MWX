// -*- coding:utf-8-unix -*-
/*!
  @file   AQM0802.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Wed Nov  4 23:01:28 2020
  @version 1.0a

  @brief  A MWX Driver for AQM0802 LCD with Sitronix ST7032i Controller

  A Part of the Willow eXtension Library.

  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef AQM0802_H
#define AQM0802_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include <stdarg.h>
#include "wxcommon.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

enum CtrlByte_e {
  INSTRUCTION = 0x00,
  DATA = 0x40
};

// Class //////////////////////////////////////////////////////////////////////
class AQM0802 {
private:
  static bool hasInit;

  // I2C slave address for ST7032i
  uint8_t slaveAddress;
  uint8_t currentRow;

  void writeByte(const CtrlByte_e type, const uint8_t data);

public:
  AQM0802(void);
  ~AQM0802(void);
  void init(void);
  void clearAll(void);
  void setCursorAt(const uint8_t row, const uint8_t col);
  void putc(const char data);
  int printf(const char* format, ...);
};

}
#endif
