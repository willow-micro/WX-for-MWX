// -*- coding:utf-8-unix -*-
/*!
  @file   ATP3011.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 17:04:30 2020
  @version 1.0a

  @brief  A MWX Driver for AquesTalk pico LSI ATP3011

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef ATP3011_H
#define ATP3011_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include "wxcommon.hpp"
#include "Timekeeper.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

using wx::Timekeeper;

const int PollingCycle = 15;
const int PollingTkId = 9;


// Class //////////////////////////////////////////////////////////////////////
class ATP3011 {
private:
  static bool hasInit;
  static bool isAvailable;

private:
  static void ISR_polling(void);

public:
  ATP3011(void);
  ~ATP3011(void);
  void init(void);
  result_e speech(const char* fstr);
  bool available(void);

};

}
#endif
