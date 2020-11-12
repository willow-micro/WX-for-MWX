// -*- coding:utf-8-unix -*-
/*!
  @file   Timekeeper.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 23:52:17 2020
  @version 1.0a

  @brief  Call a function after a specified delay or repeatedly at a specified rate

  NOTE: This is a SINGLETON class.

  @see    alarm/cyclic id: 0-9

  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include "wxcommon.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

#define TIMEKEEPER_ISR_MAX 10
#define WXTIME_MAX 0xFFFFFFFF

// Timekeeper ISR function pointer type
typedef void (* timekeeperISRPtr_t)(void);


// Class //////////////////////////////////////////////////////////////////////
class Timekeeper {
private:
  static bool hasInit;

  uint32_t wxTime;

  timekeeperISRPtr_t alarmISRPtrArray[TIMEKEEPER_ISR_MAX];
  timekeeperISRPtr_t cyclicISRPtrArray[TIMEKEEPER_ISR_MAX];
  uint32_t alarmDelayTimeArray[TIMEKEEPER_ISR_MAX];
  uint32_t cyclicCycleTimeArray[TIMEKEEPER_ISR_MAX];
  uint32_t alarmLastTimeArray[TIMEKEEPER_ISR_MAX];
  uint32_t cyclicLastTimeArray[TIMEKEEPER_ISR_MAX];
  bool alarmEnableArray[TIMEKEEPER_ISR_MAX];
  bool cyclicEnableArray[TIMEKEEPER_ISR_MAX];

private:
  Timekeeper(void);
  ~Timekeeper(void);
  static Timekeeper instance;

public:
  static Timekeeper& getInstance() {
    // Because of a limitation of JN516x, cannot use static instance in a static method.
    // static Timekeeper tk;
    // return tk;
    return instance;
  }

public:
  void init(void);
  void updateEveryMs(void);
  void startAlarm(const int id, timekeeperISRPtr_t isr, const uint32_t delayTimeMs);
  void startCyclic(const int id, timekeeperISRPtr_t isr, const uint32_t cycleTimeMs);
  void stopAlarm(const int id);
  void stopCyclic(const int id);
};

}
#endif
