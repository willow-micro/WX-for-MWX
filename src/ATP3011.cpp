// -*- coding:utf-8-unix -*-
/*!
  @file   ATP3011.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 17:07:11 2020
  @version 1.0a

  @brief  A MWX Driver for AquesTalk pico LSI ATP3011

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "ATP3011.hpp"

// Methods ////////////////////////////////////////////////////////////////////

wx::ATP3011::ATP3011(void)
  : isAvailable(false)
{
  return;
}

wx::ATP3011::~ATP3011(void)
{
  return;
}

void wx::ATP3011::init(void)
{
  this->isAvailable = false;

  // Required: 2400bps~76800bps
  Serial.begin(9600);

  // Baudrate auto set
  Serial.putchar('?');

  return;
}

void wx::ATP3011::speech(const char* const fstr)
{
  if (!(this->isAvailable)) {
    return;
  }

  Serial.printfmt("%s\r", fstr);
  this->isAvailable = false;

  return;
}

bool wx::ATP3011::available(void)
{
  uint8_t c;
  if (Serial.available()) {
    c = Serial.read();
    switch (c) {
    case '>':
      this->isAvailable = true;
      break;
    default:
      break;
    }
  }

  return this->isAvailable;
}
