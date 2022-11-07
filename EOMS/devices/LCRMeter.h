//==============================================================================
//
// Title:		LCRMeter.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-09-24 at 21:12:44 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __LCRMeter_H__
#define __LCRMeter_H__

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
typedef struct LCRMeter
{
    Device device;
   
}LCRMeter;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void LCRMeterInit(LCRMeter * pDev);
void LCRMeterDeinit(LCRMeter * pDev);



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LCRMeter_H__ */
