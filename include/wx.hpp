/*!
  @file   wx.hpp
  @author Takuma Kawamura <kawa@macbook-pro-2015.local>
  @date   Thu Nov  5 18:55:07 2020

  @brief  Willow eXtension Library Header

  @copyright 2020 (C) Takuma Kawamura All Rights Reserved.
*/


#include "AQM0802.hpp"
#include "ATP3011.hpp"
#include "FIFO.hpp"
#include "Timekeeper.hpp"

namespace wx {

#define InitGlobalObject(className,objName)   objName = new ((void*)&objName) className()

}
