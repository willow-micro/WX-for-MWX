// -*- coding:utf-8-unix -*-
/*!
  @file   SerialUnpacker.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Fri Nov 20 20:59:29 2020
  @version 1.0a

  @brief  Collect Data and Unpack Packets for Serial Connections

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef SerialUnpacker_H
#define SerialUnpacker_H

// Modules ////////////////////////////////////////////////////////////////////
#include <TWELITE>
#include <string.h>
#include "wxcommon.hpp"

// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

enum serial_unpacker_state_e {
  WAITING_FOR_HEADER,
  WAITING_FOR_LENGTH,
  COLLECTING_PAYLOAD,
  WAITING_FOR_CHECKSUM,
  WAITING_FOR_FOOTER
}

// Class //////////////////////////////////////////////////////////////////////
class SerialUnpacker {
private:
  serial_unpacker_state_e state;
  int payloadLength;
  uint8_t payloadBuffer[WX_SERIAL_PACKET_MAX_PAYLOAD_LENGTH];
  int payloadBufferIndex;
  uint8_t checksum;

public:
  SerialUnpacker(void);
  ~SerialUnpacker(void);
  void init(void);
  bool available(const uint8_t fragment);
  uint8_t unpackPayloadAt(const int index);
};

}

#endif
