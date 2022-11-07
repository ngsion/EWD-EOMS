//==============================================================================
//
// Title:		Admesy.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-11-07 at 9:53:33 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Admesy_H__
#define __Admesy_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
  #include "Device.h" 
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct Admesy
{
    Device device;


}Admesy;

//==============================================================================
// External variables

//==============================================================================
// Global functions
//==============================================================================
// Global functions
void AdmesyInit(Admesy * pDev);
void AdmesyDeinit(Admesy * pDev);



#endif  /* ndef __Admesy_H__ */
