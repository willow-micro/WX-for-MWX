// -*- coding:utf-8-unix -*-
/*!
  @file   SerialPacker.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Fri Nov 20 20:39:19 2020
  @version 1.0a

  @brief  Pack a Byte Array Packet for Serial Connections

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "SerialPacker.hpp"


wx::SerialPacker::SerialPacker(void)
{
  return;
}

wx::SerialPacker::~SerialPacker(void)
{
  return;
}

void wx::SerialPacker::init(void)
{
  return;
}

wx::result_e wx::SerialPacker::pack(uint8_t* srcBuffer, const uint8_t srcLength, uint8_t* destBuffer)
{
  if (srcLength <= 0) {
    return WX_ERROR;
  }

  // Header
  *(destBuffer++) = WX_SERIAL_PACKET_HEADER;
  // Length
  *(destBuffer++) = srcLength;
  // Payload
  uint8_t checksum = 0;
  for (int i = 0; i < srcLength; i++) {
    *(destBuffer++) = *(srcBuffer);
    checksum += *(srcBuffer++);
  }
  // Checksum
  *(destBuffer++) = checksum;
  // Footer
  *(destBuffer++) = WX_SERIAL_PACKET_FOOTER;

  return WX_OK;
}
