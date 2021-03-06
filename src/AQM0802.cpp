// -*- coding:utf-8-unix -*-
/*!
  @file   AQM0802.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Wed Nov  4 23:26:21 2020
  @version 1.0a

  @brief  A MWX Driver for AQM0802 LCD with Sitronix ST7032i Controller

  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "AQM0802.hpp"


// Methods ////////////////////////////////////////////////////////////////////
wx::AQM0802::AQM0802(void)
  // : slaveAddress(0x3E),
  //   currentRow(0)
{
  return;
}

wx::AQM0802::~AQM0802(void)
{
  return;
}

void wx::AQM0802::writeByte(const CtrlByte_e type, const uint8_t data)
{
  // data is always 1Byte (Co=0)
  Wire.beginTransmission(this->slaveAddress);
  Wire.write(type);
  Wire.write(data);
  Wire.endTransmission(true);
  delayMicroseconds(30);

  return;
}

void wx::AQM0802::init(void)
{
  this->slaveAddress = 0x3E;
  this->currentRow = 0;

  Wire.begin(WIRE_CONF::WIRE_400KHZ, false);
  delay(40);
  // Function Set: 8-bit bus, 2-line, normal font, normal instruction
  wx::AQM0802::writeByte(INSTRUCTION, 0x38);
  // Function Set: 8-bit bus, 2-line, normal font, extension instruction
  wx::AQM0802::writeByte(INSTRUCTION, 0x39);
  // Internal OSC Freq: bias 1/5, freq 183Hz
  wx::AQM0802::writeByte(INSTRUCTION, 0x14);
  // Contrast set (low byte): C3,C2,C1,C0=0
  wx::AQM0802::writeByte(INSTRUCTION, 0x70);
  // Power/ICON ctrl / Contrast set (high byte): ICON off, booster on(if3.3V), C5=1
  wx::AQM0802::writeByte(INSTRUCTION, 0x56);
  // Follower ctrl: follower on, Rab2=1
  wx::AQM0802::writeByte(INSTRUCTION, 0x6C);
  delay(200);
  // Function Set: 8-bit bus, 2-line, normal font, normal instruction
  wx::AQM0802::writeByte(INSTRUCTION, 0x38);
  // Display ON/OFF: display on, cursor disappears, cursor blink off
  wx::AQM0802::writeByte(INSTRUCTION, 0x0C);
  // Clear Display
  wx::AQM0802::writeByte(INSTRUCTION, 0x01);
  delay(1);

  this->currentRow = 0;

  return;
}

void wx::AQM0802::clearAll(void)
{
  wx::AQM0802::writeByte(INSTRUCTION, 0x01);
  delay(1);
  this->currentRow = 0;

  return;
}

void wx::AQM0802::setCursorAt(const uint8_t row, const uint8_t col)
{
  uint8_t acAddress = 0x00;            // 7Bits

  acAddress |= ( row % 2 == 0 ) ? 0x00 : 0x40;
  acAddress |= col;

  wx::AQM0802::writeByte(INSTRUCTION, ( acAddress | 0x80 ));
  this->currentRow = row;

  return;
}

void wx::AQM0802::putc(const char c)
{
  wx::AQM0802::writeByte(DATA, static_cast<uint8_t>(c));

  return;
}

int wx::AQM0802::printf(const char* format, ...)
{
  int wroteLength = 0;
  char stringBuffer[128];

  memset(stringBuffer, 0, 128);

  va_list arg;
  va_start(arg, format);
  wroteLength = vsnprintf_(stringBuffer, 128, format, arg); // vsnprintf_ in TWENET
  va_end(arg);

  if (wroteLength < 0 || wroteLength > 128) {
    return 0;
  }

  int currentLineCharCount = 0;
  for (int i = 0; i < wroteLength; i++) {
    if (stringBuffer[i] == '\n') {
      // go to new line
      wx::AQM0802::setCursorAt(this->currentRow + 1, 0);
      currentLineCharCount = 0;
    } else if (currentLineCharCount % 8 == 0 && currentLineCharCount != 0) {
      // go to new char
      wx::AQM0802::setCursorAt(this->currentRow + 1, 0);
      // put the letter
      wx::AQM0802::putc(stringBuffer[i]);
      currentLineCharCount++;
    } else {
      wx::AQM0802::putc(stringBuffer[i]);
      currentLineCharCount++;
    }
  }

  return wroteLength;
}
