// -*- coding:utf-8-unix -*-
/*!
  @file   wxcommon.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov 12 08:14:39 2020

  @brief  Willow eXtension Library Common Defs

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef WXCOMMON_H
#define WXCOMMON_H

#include <TWELITE>

namespace wx {

// Assembly Command ///////////////////////////////////////////////////////////
// NOP
// This macro is usable at ONLY JN516x Series.
#define NOP asm volatile ("b.nop;")

// Disable all interuupts and save the status of interrupts.
// This macro is usable at ONLY JN516x Series.
#define DISABLE_INTERRUPTS asm volatile ("b.di;" : : )

// Enable all interuupts when the status of interrupts is ENABLED.
// This macro is usable at ONLY JN516x Series.
#define RESTORE_INTERUUPTS asm volatile ("b.ei;" : : )

// Enum ///////////////////////////////////////////////////////////////////////
enum result_e {
  WX_OK, WX_ERROR
};


// Serial Packet for Packer / Unpacker ////////////////////////////////////////
#define WX_SERIAL_PACKET_HEADER 0x40  // At Mark, '@'
#define WX_SERIAL_PACKET_FOOTER 0x0A  // New Line aka LF, '\n'
#define WX_SERIAL_PACKET_MAX_PAYLOAD_LENGTH 256

// Basic Utils ////////////////////////////////////////////////////////////////
inline bool isPullupButtonOn(uint32_t state, uint32_t mask, uint8_t pinNum)
{
  if ((~(mask & 0x80000000) & ~(state & (1UL << pinNum))) == 0xFFFFFFFF) {
    return true;
  }
  return false;
}

}

#endif
