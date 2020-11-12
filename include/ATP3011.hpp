// -*- coding:utf-8-unix -*-
/*!
  @file   ATP3011.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 17:04:30 2020
  @version 1.0a

  @brief  A MWX Driver for AquesTalk pico LSI ATP3011

  NOTE: This is a SINGLETON class.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef ATP3011_H
#define ATP3011_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include "wxcommon.hpp"
#include "Timekeeper.hpp"
#include "FIFO.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

using wx::Timekeeper;
using wx::FIFO;

#define ATP3011_MAX_MESSAGES 16
#define ATP3011_MAX_MESSAGE_LENGTH 256
#define ATP3011_MAX_RESERVATIONS 8
#define ATP3011_POLLING_CYCLE 15
#define ATP3011_POLLING_TIMEKEEPER_ID 9


// Class //////////////////////////////////////////////////////////////////////
class ATP3011 {
private:
  static bool isAvailable;
  char messages[ATP3011_MAX_MESSAGES][ATP3011_MAX_MESSAGE_LENGTH];
  FIFO<uint8_t> *reservationIdQueue;

private:
  static void ISR_polling(void);

private:
  ATP3011(void);
  ~ATP3011(void);
  static ATP3011 instance;

public:
  static ATP3011& getInstance() {
    return instance;
  }

public:
  void init(void);
  bool available(void);
  void registerMessage(const int id, const char* fstr);
  void requestMessage(const int id);
  void update(void);

private:
  result_e speech(const char* fstr);

};

}
#endif
