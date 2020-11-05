// -*- coding:utf-8-unix -*-
/*!
  @file   FIFO.cpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 17:32:26 2020
  @version 2.2

  @brief  Variable Length Ring Buffer

  @see This will overwrite when the buffer is full.

  Ported from Mbed OS 2.0.
  Depending on C++11.

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/

#include "FIFO.hpp"

// Methods ////////////////////////////////////////////////////////////////////
template <class T>
wx::FIFO<T>::FIFO(uint32_t bufsize)
  : buffer{new T[bufsize]},
    size{bufsize},
    getindex{0},
    putindex{0},
    count{0}
{
  // this->buffer = new T[bufsize];
  // this->size = bufsize;
  // this->getindex = 0;
  // this->putindex = 0;
  // this->count = 0;
  return;
}

template <class T>
wx::FIFO<T>::~FIFO(void){
  //delete[] buffer;              // Cannot delete on the MWX
  return;
}

template <class T>
void wx::FIFO<T>::clear(void){
  DISABLE_INTERRUPTS;

  this->count = 0;
  this->getindex = 0;
  this->putindex = 0;

  RESTORE_INTERUUPTS;

  return;
}

template <class T>
uint32_t wx::FIFO<T>::getsize(void){
  return this->size;
}

template <class T>
T wx::FIFO<T>::get(void){
  T getdata;

  DISABLE_INTERRUPTS;

  if (this->count <= 0) {
    RESTORE_INTERUUPTS;
    return 0;
  }

  getdata = this->buffer[this->getindex];
  this->getindex++;
  if (this->getindex >= this->size) {  //When the index is in the terminus of the buffer
    this->getindex = 0;
  }
  this->count--;

  RESTORE_INTERUUPTS;

  return getdata;
}

template <class T>
T wx::FIFO<T>::peek(void){
  T getdata;

  DISABLE_INTERRUPTS;

  if (this->count <= 0) {  //When the buffer is empty
    RESTORE_INTERUUPTS;
    return 0;
  }
  getdata = this->buffer[this->getindex];

  RESTORE_INTERUUPTS;
  return getdata;
}

template <class T>
void wx::FIFO<T>::put(const T putdata){
  DISABLE_INTERRUPTS;

  this->buffer[this->putindex] = putdata;
  this->putindex++;
  if (this->putindex >= this->size) {  // When the index is in the terminus of the buffer
    this->putindex = 0;
  }
  this->count++;

  RESTORE_INTERUUPTS;

  return;
}

template <class T>
uint32_t wx::FIFO<T>::available(void){
  uint32_t c = 0;

  DISABLE_INTERRUPTS;

  c = this->count;

  RESTORE_INTERUUPTS;

  return c;
}

// Initial explicit instantiation of class template
template class wx::FIFO<uint8_t>;
template class wx::FIFO<int8_t>;
template class wx::FIFO<uint16_t>;
template class wx::FIFO<int16_t>;
template class wx::FIFO<uint32_t>;
template class wx::FIFO<int32_t>;
template class wx::FIFO<uint64_t>;
template class wx::FIFO<int64_t>;
template class wx::FIFO<char>;
template class wx::FIFO<wchar_t>;
