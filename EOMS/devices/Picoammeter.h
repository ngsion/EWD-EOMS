//==============================================================================
//
// Title:		Picoammeter.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-18 at 12:01:43 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Picoammeter_H__
#define __Picoammeter_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Device.h"
#include "PicoSetting.h"


//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct Picoammeter
{
    Device device;

    
}Picoammeter;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void PicoammeterInit(Picoammeter * pDev);
void PicoammeterDeinit(Picoammeter * pDev);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Picoammeter_H__ */
