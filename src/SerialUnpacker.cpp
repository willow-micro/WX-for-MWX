// -*- coding:utf-8-unix -*-
/*!
  @file   SerialUnpacker.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Fri Nov 20 21:08:13 2020
  @version 1.0a

  @brief  Collect Data and Unpack Packets for Serial Connections

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "SerialUnpacker.hpp"


wx::SerialUnpacker::SerialUnpacker(void)
{
  return;
}

wx::SerialUnpacker::~SerialUnpacker(void)
{
  return;
}


void wx::SerialUnpacker::init(void)
{
  this->state = WAITING_FOR_HEADER;
  this->payloadLength = 0;
  memset(this->payloadBuffer, 0x00, WX_SERIAL_PACKET_MAX_PAYLOAD_LENGTH);
  this->payloadBufferIndex = 0;
  this->checksum = 0;

  return;
}


bool wx::SerialUnpacker::available(const uint8_t fragment)
{
  bool isAvailable = false;

  switch (this->state) {
  case WAITING_FOR_HEADER:
    if (fragment == WX_SERIAL_PACKET_HEADER) {
      this->state = WAITING_FOR_LENGTH;
      this->payloadLength = 0;
      this->payloadBufferIndex = 0;
      this->checksum = 0;
    }
    break;
  case WAITING_FOR_LENGTH:
    this->state = COLLECTING_PAYLOAD;
    this->payloadLength = fragment;
    break;
  case COLLECTING_PAYLOAD:
    if (this->payloadBufferIndex < this->payloadLength) {
      this->payloadBuffer[this->payloadBufferIndex++] = fragment;
      this->checksum += fragment;
    } else if (this->payloadBufferIndex == this->payloadLength) {
      this->state = WAITING_FOR_CHECKSUM;
    } else {
      this->state = WAITING_FOR_HEADER;
    }
    break;
  case WAITING_FOR_CHECKSUM:
    if (fragment == this->checksum) {
      this->state = WAITING_FOR_FOOTER;
    } else {
      this->state = WAITING_FOR_HEADER;
    }
    break;
  case WAITING_FOR_FOOTER:
    if (fragment == WX_SERIAL_PACKET_FOOTER) {
      this->state = WAITING_FOR_HEADER;
      isAvailable = true;
    }
    break;
  default:
    this->state = WAITING_FOR_HEADER;
    break;

  return isAvailable;
}

uint8_t unpackPayloadAt(const int index)
{
  return this->payloadBuffer[index];
}
