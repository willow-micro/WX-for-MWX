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


bool wx::ATP3011::isAvailable = false;

// Because of a limitation of JN516x, cannot use static instance in a static method.
// So, initialize the private static member instance here.
wx::ATP3011 wx::ATP3011::instance = wx::ATP3011();


// Methods ////////////////////////////////////////////////////////////////////

void wx::ATP3011::ISR_polling(void)
{
  if (wx::ATP3011::isAvailable) {
    return;
  }

  if (auto&& trs = SPI.get_rwer()) {
    uint8_t response;
    trs << 0xFF;
    trs >> response;
    if (response == '>') {
      wx::Timekeeper::getInstance().stopCyclic(ATP3011_POLLING_TIMEKEEPER_ID);
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
  // Initialize messages
  for (int i = 0; i < ATP3011_MAX_MESSAGES; i++) {
    memset(this->messages[i], ' ', ATP3011_MAX_MESSAGE_LENGTH - 1);
    this->messages[i][ATP3011_MAX_MESSAGE_LENGTH - 1] = '\0';
  }

  // Initialize reservation queue
  this->reservationIdQueue = new FIFO<uint8_t>();
  this->reservationIdQueue->init(ATP3011_MAX_RESERVATIONS);
  this->reservationIdQueue->clear();

  // Initialize SPI with 500KHz, MSB First, Mode3
  SPI.begin(0, SPISettings(500000, SPI_CONF::MSBFIRST, SPI_CONF::SPI_MODE3));

  // Timekeeper for polling
  wx::Timekeeper::getInstance().init();

  wx::ATP3011::isAvailable = true;

  return;
}

bool wx::ATP3011::available(void)
{
  return wx::ATP3011::isAvailable;
}

void wx::ATP3011::registerMessage(const int id, const char* fstr)
{
  int i;
  for (i = 0; fstr[i] != '\0'; i++) {
    this->messages[id][i] = fstr[i];
  }
  this->messages[id][i] = '\r';

  return;
}

void wx::ATP3011::requestMessage(const int id)
{
  this->reservationIdQueue->put(id);
  return;
}

void wx::ATP3011::update(void)
{
  if (wx::ATP3011::isAvailable && this->reservationIdQueue->available()) {
    uint8_t id = this->reservationIdQueue->get();
    wx::ATP3011::speech(this->messages[id]);
  }
  return;
}


wx::result_e wx::ATP3011::speech(const char* fstr)
{
  if (!(wx::ATP3011::isAvailable)) {
    return WX_ERROR;
  }

  if (auto&& trs = SPI.get_rwer()) {
    uint8_t response;

    while (*(fstr) != '\r' && *(fstr) != '\0') {
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
  wx::Timekeeper::getInstance().startCyclic(ATP3011_POLLING_TIMEKEEPER_ID,
                                            &(wx::ATP3011::ISR_polling),
                                            ATP3011_POLLING_CYCLE);

  return WX_OK;
}
