// -*- coding:utf-8-unix -*-
/*!
  @file   OLED128x64.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Sun Jan 17 22:36:13 2021
  @version 0.1

  @brief  A MWX Driver for OLED 128x64 Display with Solomon Systech SSD1306 Controller

  A Part of the Willow eXtension Library.
  Depending on C++11.

  @copyright 2021 (C) Takuma Kawamura All Rights Reserved.
*/

#include "OLED128x64.hpp"


// Methods ////////////////////////////////////////////////////////////////////
wx::OLED128x64::OLED128x64(void)
  // : slaveAddress(0x3C)
{
  return;
}

wx::OLED128x64::~OLED128x64(void)
{
  return;
}

void wx::OLED128x64::init(void)
{
  delay(50);

  this->slaveAddress = 0x3C;
  memset(this->vvram, 0x00, sizeof(this->vvram[0][0]) * 8 * 128);

  Wire.begin(WIRE_CONF::WIRE_400KHZ, false);

  Wire.beginTransmission(this->slaveAddress);
  // Display ON
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xAF);
  // Set OSC Freq
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xD5);
  Wire.write(0xA0);             // Suitable for video
  // Set MUX Ratio
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xA8);
  Wire.write(0x3F);
  // Set Display Offset
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xD3);
  Wire.write(0x00);
  // Set Display Start Line
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0x40);
  // Enable Charge Pump Regulator
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0x8D);
  Wire.write(0x14);
  // // Set Memory Addressing Mode: Horizontal Addressing Mode
  // Wire.write(SSD1306_INSTRUCTION_MUL);
  // Wire.write(0x20);
  // Wire.write(0x00);
  // Set Column Address Range
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0x21);
  Wire.write(0x00);
  Wire.write(0x7F);
  // // Set Page Address Range
  // Wire.write(SSD1306_INSTRUCTION_MUL);
  // Wire.write(0x22);
  // Wire.write(0x00);
  // Wire.write(0x07);
  // Set Segment Re-map (Flip Horizontally)
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xA1);
  // Set COM Output Scan Direction
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xC8);
  // Set COM Pins Hardware Config
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xDA);
  Wire.write(0x12);
  // Set Contrast Control
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0x81);
  Wire.write(0xCF);
  // Set Precharge Period
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xD9);
  Wire.write(0xF1);
  // Set VCOMH Deselect Level
  Wire.write(SSD1306_INSTRUCTION_MUL);
  Wire.write(0xDB);
  Wire.write(0x20);
  // Disable Entire Display ON (Enable GDDRAM)
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xA4);
  // Set Normal/Inverse Display
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xA6);
  // Display ON
  Wire.write(SSD1306_INSTRUCTION);
  Wire.write(0xAF);

  Wire.endTransmission(true);
  return;
}

void wx::OLED128x64::clearAll(void)
{
  memset(this->vvram, 0x00, sizeof(this->vvram[0][0]) * 8 * 128);
  return;
}

void wx::OLED128x64::clearRegion(const int x0, const int x1, const int y0, const int y1)
{
  for (int y = y0; y <= y1; y++) {
    for (int x = x0; x <= x1; x++) {
      this->drawPointAt(x, y, 0x00);
    }
  }
  return;
}

void wx::OLED128x64::invertColor(void)
{
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 128; j++) {
      this->vvram[i][j] = ~this->vvram[i][j];
    }
  }
  return;
}

void wx::OLED128x64::invertRegionColor(const int x0, const int x1, const int y0, const int y1)
{
  for (int x = x0; x <= x1; x++) {
    for (int y = y0; y <= y1; y++) {
      this->vvram[static_cast<int>(y / 8)][x] ^= (1 << (y % 8));
    }
  }
  return;
}

void wx::OLED128x64::update(void)
{
  for (int i = 0; i < 8; i++) {
    // Set Page
    Wire.beginTransmission(this->slaveAddress);
    Wire.write(SSD1306_INSTRUCTION);
    Wire.write(0xB0 | i);
    Wire.endTransmission(true);
    // Write Data
    Wire.beginTransmission(this->slaveAddress);
    Wire.write(SSD1306_DATA_MUL);
    for (int j = 0; j < 128; j++) {
      Wire.write(this->vvram[i][j]);
    }
    Wire.endTransmission(true);
  }
  return;
}

void wx::OLED128x64::drawPointAt(const int x, const int y, const int value)
{
  if (x >= 128 || y >= 64 || x < 0 || y < 0 || value < 0) {
    return;
  }
  if (value > 0) {
    this->vvram[static_cast<int>(y / 8)][x] |= (1 << (y % 8));
  } else {
    this->vvram[static_cast<int>(y / 8)][x] &= ~(1 << (y % 8));
  }
  return;
}

void wx::OLED128x64::drawLine(int x0, const int x1, int y0, const int y1)
{
  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);
  if (dx == 0) {
    // Vertical Line
    for (int y = y0; y <= y1; y++) {
      this->drawPointAt(x0, y, 1);
    }
  } else if (dy == 0) {
    // Horizontal Line
    for (int x = x0; x <= x1; x++) {
      this->drawPointAt(x, y0, 1);
    }
  } else {
    // Slanting Line
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while(1) {
      this->drawPointAt(x0, y0, 1);
      if (x0 == x1 && y0 == y1) {
        break;
      }
      int err2 = 2 * err;
      if (err2 > -dy) {
        err -= dy;
        x0 += sx;
      }
      if (err2 < dx) {
        err += dx;
        y0 += sy;
      }
    }
  }

  return;
}

void wx::OLED128x64::drawRectangle(const int x0, const int x1, const int y0, const int y1)
{
  this->drawLine(x0, x1, y0, y0);
  this->drawLine(x0, x1, y1, y1);
  this->drawLine(x0, x0, y0, y1);
  this->drawLine(x1, x1, y0, y1);
  return;
}

void wx::OLED128x64::drawRoundRectangle(const int x0, const int x1, const int y0, const int y1)
{
  this->drawLine(x0 + 1, x1 - 1, y0, y0);
  this->drawLine(x0 + 1, x1 - 1, y1, y1);
  this->drawLine(x0, x0, y0 + 1, y1 - 1);
  this->drawLine(x1, x1, y0 + 1, y1 - 1);
  return;
}


void wx::OLED128x64::fillRegion(const int x0, const int x1, const int y0, const int y1)
{
  for (int x = x0; x <= x1; x++) {
    for (int y = y0; y <= y1; y++) {
      this->vvram[static_cast<int>(y / 8)][x] |= (1 << (y % 8));
    }
  }
  return;
}


void wx::OLED128x64::putCharAt(const int x, const int y, const char16_t c, const OLED_CharSize_e csize)
{
  const uint8_t* const bitmap = this->misaki.bitmapForCode(c);

  if (csize == OLED_CHAR_X1) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        this->drawPointAt(x + j, y + i, (bitmap[i] >> (7-j)) & 0x01);
      }
    }
  } else if (csize == OLED_CHAR_X2) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        this->drawPointAt(x + j*2, y + i*2, (bitmap[i] >> (7-j)) & 0x01);
        this->drawPointAt(x + j*2 + 1, y + i*2, (bitmap[i] >> (7-j)) & 0x01);
        this->drawPointAt(x + j*2, y + i*2 + 1, (bitmap[i] >> (7-j)) & 0x01);
        this->drawPointAt(x + j*2 + 1, y + i*2 + 1, (bitmap[i] >> (7-j)) & 0x01);
      }
    }
  }

  return;
}

void wx::OLED128x64::println(const int x, const int y, const char16_t* const str, const int len, const OLED_CharSize_e csize)
{
  for (int i = 0; i < len; i++) {
    if (str[i] == L'\0') {
      break;
    }

    if (csize == OLED_CHAR_X1) {
      this->putCharAt(8*i + x, y, str[i], wx::OLED_CHAR_X1);
    } else if (csize == OLED_CHAR_X2) {
      this->putCharAt(16*i + x, y, str[i], wx::OLED_CHAR_X2);
    }
  }

  return;
}

void wx::OLED128x64::println(const int row, const char16_t* const str, const int len, const OLED_CharSize_e csize)
{
  for (int i = 0; i < len; i++) {
    if (str[i] == L'\0') {
      break;
    }

    if (csize == OLED_CHAR_X1) {
      this->putCharAt(8*i, row*8, str[i], wx::OLED_CHAR_X1);
    } else if (csize == OLED_CHAR_X2) {
      this->putCharAt(16*i, row*16, str[i], wx::OLED_CHAR_X2);
    }
  }

  return;
}

void wx::OLED128x64::drawBitmap(const int x, const int y, const uint8_t* data, const int cols, const int startRow, const int endRow)
{
  for (int row = startRow; row <= endRow; row++) {
    for (int col = 0; col < cols; col++) {
      for (int bit = 7; bit >= 0; bit--) {
        this->drawPointAt(x + col, y + ((row-startRow)*8) + bit, (*(data + cols*row + col) >> bit) & 0x01);
      }
    }
  }
  return;
}

void wx::OLED128x64::drawBitmapWithCovering(const int x, const int y, const uint8_t* data, const int cols, const int startRow, const int endRow, const int coverSize, bool* keys, const int keyCount)
{
  //this->fillRegion(x, x+cols-1, y, y+((endRow-startRow+1)*8));

  for (int row = startRow; row <= endRow; row++) {
    for (int col = 0; col < cols; col++) {
      int colSeq = col % (keyCount * coverSize);
      int colKeyIndex = static_cast<int>(colSeq / coverSize);
      bool isColAllowToDecrypt = *(keys+colKeyIndex);
      if (isColAllowToDecrypt) {
        for (int bit = 7; bit >= 0; bit--) {
          int bitSeq = bit % (keyCount * coverSize);
          int bitKeyIndex = static_cast<int>(bitSeq / coverSize);
          bool isBitAllowToDecrypt = *(keys+bitKeyIndex);
          if (isBitAllowToDecrypt) {
            this->drawPointAt(x + col, y + ((row-startRow)*8) + bit, (*(data + cols*row + col) >> bit) & 0x01);
          }
        }
      }
    }
  }

  return;
}
