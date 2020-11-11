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

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

// Class //////////////////////////////////////////////////////////////////////
class ATP3011 {
private:
  bool isAvailable;

public:
  ATP3011(void);
  ~ATP3011(void);
  void init(void);
  void speech(const char* const fstr);
  bool available(void);
};

}
#endif
