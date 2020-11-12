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

// Initialize the state of instance
bool wx::ATP3011::hasInit = false;
bool wx::ATP3011::isAvailable = false;

// Methods ////////////////////////////////////////////////////////////////////

void wx::ATP3011::ISR_polling(void)
{
  if (wx::ATP3011::isAvailable || !wx::ATP3011::hasInit) {
    return;
  }

  if (auto&& trs = SPI.get_rwer()) {
    uint8_t response;
    trs << 0xFF;
    trs >> response;
    if (response == '>') {
      wx::Timekeeper::getInstance().stopCyclic(PollingTkId);
      wx::ATP3011::isAvailable = true;
      return;
    }
  }

  return;
}


wx::ATP3011::ATP3011(void)
{
  return;
}

wx::ATP3011::~ATP3011(void)
{
  return;
}

void wx::ATP3011::init(void)
{
  // Initialize SPI with 500KHz, MSB First, Mode3
  SPI.begin(0, SPISettings(500000, SPI_CONF::MSBFIRST, SPI_CONF::SPI_MODE3));

  // Timekeeper for polling
  wx::Timekeeper::getInstance().init();

  wx::ATP3011::hasInit = true;
  wx::ATP3011::isAvailable = true;

  return;
}

wx::result_e wx::ATP3011::speech(const char* fstr)
{
  if (!(wx::ATP3011::isAvailable) || !(wx::ATP3011::hasInit)) {
    return WX_ERROR;
  }

  if (auto&& trs = SPI.get_rwer()) {
    uint8_t response;

    while (*(fstr) != '\r') {
      trs << *(fstr++);
      trs >> response;
      if (response != '>') {
        return WX_ERROR;
      }
    }

    trs << '\r';
    trs >> response;
    if (response != '>') {
      return WX_ERROR;
    }
  }

  wx::ATP3011::isAvailable = false;
  wx::Timekeeper::getInstance().startCyclic(PollingTkId, &(wx::ATP3011::ISR_polling), PollingCycle);

  return WX_OK;
}

bool wx::ATP3011::available(void)
{
  return wx::ATP3011::isAvailable;
}
