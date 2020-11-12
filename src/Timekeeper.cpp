// -*- coding:utf-8-unix -*-
/*!
  @file   Timekeeper.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 23:45:38 2020
  @version 1.0a

  @brief  Call a function after a specified delay or repeatedly at a specified rate

  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "Timekeeper.hpp"


// Initialize the state of instance
bool wx::Timekeeper::hasInit = false;

// Because of a limitation of JN516x, cannot use static instance in a static method.
// So, initialize the private static member instance here.
wx::Timekeeper wx::Timekeeper::instance = wx::Timekeeper();


// Methods ////////////////////////////////////////////////////////////////////

wx::Timekeeper::Timekeeper(void)
  // : wxTime{0},
  //   alarmISRPtrArray{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
  //   cyclicISRPtrArray{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
  //   alarmDelayTimeArray{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  //   cyclicCycleTimeArray{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  //   alarmLastTimeArray{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  //   cyclicLastTimeArray{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  //   alarmEnableArray{false, false, false, false, false, false, false, false, false, false},
  //   cyclicEnableArray{false, false, false, false, false, false, false, false, false, false}
{
  return;
}

wx::Timekeeper::~Timekeeper(void)
{
  return;
}

void wx::Timekeeper::init(void)
{
  if (hasInit) {
    return;
  }

  wxTime = 0;
  for (int i = 0; i < TIMEKEEPER_ISR_MAX; i++) {
    alarmISRPtrArray[i] = NULL;
    cyclicISRPtrArray[i] = NULL;
    alarmDelayTimeArray[i] = 0;
    cyclicCycleTimeArray[i] = 0;
    alarmLastTimeArray[i] = 0;
    cyclicLastTimeArray[i] = 0;
    alarmEnableArray[i] = false;
    cyclicEnableArray[i] = false;
  }
  hasInit = true;

  return;
}

void wx::Timekeeper::updateEveryMs(void)
{
  if (!hasInit) {
    return;
  }

  // Increment the wxTime
  this->wxTime = (this->wxTime < WXTIME_MAX) ? this->wxTime + 1 : 0;

  // Alarm
  for (int id = 0; id < TIMEKEEPER_ISR_MAX; id++) {
    // If the alarm is enabled
    if (this->alarmEnableArray[id] == true) {
      // Get interval from setting the alarm
      int interval = this->wxTime - this->alarmLastTimeArray[id];
      // If wxTime overflowed
      if (interval < 0) {
        interval += WXTIME_MAX;
      }
      // Check the delay time is exceeded or not
      if (static_cast<uint32_t>(interval) >= this->alarmDelayTimeArray[id] ) {
        // Execute the function
        this->alarmISRPtrArray[id]();
        // Reset the alarm
        this->alarmISRPtrArray[id] = NULL;
        this->alarmDelayTimeArray[id] = 0;
        this->alarmLastTimeArray[id] = 0;
        this->alarmEnableArray[id] = false;
      }
    }
  }

  // Cyclic
  for (int id = 0; id < TIMEKEEPER_ISR_MAX; id++) {
    // If the cyclic is enabled
    if (this->cyclicEnableArray[id] == true) {
      // Get interval from last call
      int interval = this->wxTime - this->cyclicLastTimeArray[id];
      // If wxTime overflowed
      if (interval < 0) {
        interval += WXTIME_MAX;
      }
      // If the cycle time is exceeded
      if (static_cast<uint32_t>(interval) >= this->cyclicCycleTimeArray[id] ) {
        // Execute the function
        this->cyclicISRPtrArray[id]();
        // Prepare for the next call
        this->cyclicLastTimeArray[id] = this->wxTime;
      }
    }
  }

  return;
}

void wx::Timekeeper::startAlarm(const int id, timekeeperISRPtr_t isr, const uint32_t delayTimeMs)
{
  // If an alarm is already exists on specified id
  if (this->alarmEnableArray[id] == true) {
    return;
  }

  this->alarmISRPtrArray[id] = isr;
  this->alarmDelayTimeArray[id] = delayTimeMs;
  this->alarmLastTimeArray[id] = this->wxTime;
  this->alarmEnableArray[id] = true;

  return;
}

void wx::Timekeeper::startCyclic(const int id, timekeeperISRPtr_t isr, const uint32_t cycleTimeMs)
{
  // If an cyclic is already exists on specified id
  if (this->cyclicEnableArray[id] == true) {
    return;
  }

  this->cyclicISRPtrArray[id] = isr;
  this->cyclicCycleTimeArray[id] = cycleTimeMs;
  this->cyclicLastTimeArray[id] = this->wxTime;
  this->cyclicEnableArray[id] = true;

  return;
}

void wx::Timekeeper::stopAlarm(const int id)
{
  // If an alarm is not already exists on specified id
  if (this->alarmEnableArray[id] == false) {
    return;
  }

  this->alarmISRPtrArray[id] = NULL;
  this->alarmDelayTimeArray[id] = 0;
  this->alarmLastTimeArray[id] = 0;
  this->alarmEnableArray[id] = false;

  return;
}

void wx::Timekeeper::stopCyclic(const int id)
{
  // If an cyclic is not already exists on specified id
  if (this->cyclicEnableArray[id] == false) {
    return;
  }

  this->cyclicISRPtrArray[id] = NULL;
  this->cyclicCycleTimeArray[id] = 0;
  this->cyclicLastTimeArray[id] = 0;
  this->cyclicEnableArray[id] = false;

  return;
}
