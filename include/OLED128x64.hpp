// -*- coding:utf-8-unix -*-
/*!
  @file   OLED128x64.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Sun Jan 17 22:22:02 2021
  @version 0.1

  @brief  A MWX Driver for OLED 128x64 Display with Solomon Systech SSD1306 Controller

  A Part of the Willow eXtension Library.
  Depending on C++11.

  @copyright 2021 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef OLED128x64_H
#define OLED128x64_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include <math.h>
#include "wxcommon.hpp"
#include "MisakiSuperLimited.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

enum SSD1306CtrlByte_e {
  SSD1306_INSTRUCTION_MUL = 0x00,
  SSD1306_INSTRUCTION = 0x80,
  SSD1306_DATA_MUL = 0x40,
  SSD1306_DATA = 0xC0,
};

enum OLED_CharSize_e {
  OLED_CHAR_X1,
  OLED_CHAR_X2
};


// Class //////////////////////////////////////////////////////////////////////
class OLED128x64 {
private:
  // I2C slave address for SSD1306
  uint8_t slaveAddress;
  uint8_t vvram[8][128];
  MisakiSuperLimited misaki;

public:
  OLED128x64(void);
  ~OLED128x64(void);
  void init(void);
  void clearAll(void);
  void clearRegion(const int x0, const int x1, const int y0, const int y1);
  void invertColor(void);
  void invertRegionColor(const int x0, const int x1, const int y0, const int y1);
  void update(void);
  void drawPointAt(const int x, const int y, const int value);
  void drawLine(int x0, const int x1, int y0, const int y1);
  void drawRectangle(const int x0, const int x1, const int y0, const int y1);
  void drawRoundRectangle(const int x0, const int x1, const int y0, const int y1);
  void fillRegion(const int x0, const int x1, const int y0, const int y1);
  void putCharAt(const int x, const int y, const char16_t c, const OLED_CharSize_e csize);
  void putCharAt(const int x, const int y, const uint16_t c, const OLED_CharSize_e csize);
  void println(const int x, const int y, const char16_t* const str, const int len, const OLED_CharSize_e csize);
  void println(const int row, const char16_t* const str, const int len, const OLED_CharSize_e csize);
  void printNumberAt(const int x, const int y, const int num, const int digits, const OLED_CharSize_e csize);
  void printNumberAt(const int x, const int y, const float num, const int digits, const int intDigits, const OLED_CharSize_e csize);
  void drawBitmap(const int x, const int y, const uint8_t* data, const int cols, const int startRow, const int endRow);
  void drawBitmapWithCovering(const int x, const int y, const uint8_t* data, const int cols, const int startRow, const int endRow, const int coverSize, bool* keys, const int keyCount = 4);
};

}
#endif
