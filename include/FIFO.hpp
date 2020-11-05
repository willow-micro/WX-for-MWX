// -*- coding:utf-8-unix -*-
/*!
  @file   FIFO.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 17:15:33 2020
  @version 2.2

  @brief  Variable Length Ring Buffer

  @see This will overwrite when the buffer is full.

  Ported from Mbed OS 2.0.
  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#ifndef FIFO_H
#define FIFO_H

// Modules ////////////////////////////////////////////////////////////////////
#include <stdint.h>


// Definitions ////////////////////////////////////////////////////////////////
namespace wx {

// Disable all interuupts and save the status of interrupts.
// This macro is usable at ONLY JN516x Series.
#define DISABLE_INTERRUPTS asm volatile ("b.di;" : : )

// Enable all interuupts when the status of interrupts is ENABLED.
// This macro is usable at ONLY JN516x Series.
#define RESTORE_INTERUUPTS asm volatile ("b.ei;" : : )


// Class //////////////////////////////////////////////////////////////////////
//! FIFO
/*!
  @class FIFO
  @brief Variable Length Software Ring Buffer
*/
template <typename T>
class FIFO {
private:
  T *buffer;  // Buffer
  uint32_t size;  // Buffer Size
  volatile uint32_t getindex; // Index for Getting Data
  volatile uint32_t putindex; // Index for Putting Data
  volatile uint32_t count;  // Size of Data

public:
  /*!
    @brief  Create a new FIFO.
    @param  size Buffer Size.
  */
  FIFO(uint32_t bufsize);

  /*!
    @brief  Destroy the FIFO.
    @param  No Parameters.
  */
  ~FIFO(void);

  /*!
    @brief  Clear the buffer.
    @param  No Parameters.
  */
  void clear(void);

  /*!
    @brief  Get buffer size.
    @param  No Parameters.
    @return Buffer size
  */
  uint32_t getsize(void);

  /*!
    @brief  Get byte from the buffer.
    @param  No Parameters.
    @retval All Data
    @retval 0 Error.
  */
  T get(void);

  /*!
    @brief  Peek byte from the buffer
    Peek 1byte from the buffer.(Do not touch index)
    @param  No Parameters.
    @retval All Data
    @retval 0 Error.
  */
  T peek(void);

  /*!
    @brief  Put byte to the buffer
    @param  No Parameters.
    @param  putdata   The Data for Putting.
    @return Nothing.
  */
  void put(const T putdata);

  /*!
    @brief  Get Size of Retained Data.
    @param  No Parameters.
    @return Data size.
  */
  uint32_t available(void);

  /*!
   *  @brief  Overloaded operator for putting data to the FIFO.
   *  @param  Data to put
   */
  FIFO &operator= (T data){
    put(data);
    return *this;
  }

  /*!
   *  @brief  Overloaded operator for getting data from the FIFO.
   *  @param  No Parameters.
   *  @return Oldest Data
   */
  operator int(void){
    return get();
  }
};

}

#endif
