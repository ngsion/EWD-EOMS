//==============================================================================
//
// Title:		Device.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-18 at 12:12:47 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Device_H__
#define __Device_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Instrument.h"
#include <stdbool.h>
#include "Setting.h"
//==============================================================================
// Constants
#define DEVICE_TITLE_LENGTH 64


//==============================================================================
// Types
typedef struct Device
{
    unsigned int instrumentFlag;
    char  title[DEVICE_TITLE_LENGTH]; ///chinese name
    Instrument * pInstr;
    Instrument_Type * type;
    Setting * pSet;

    int (*Connect)(struct Device * pDev);
    int (*QueryID)(struct Device * pDev);
    
    int (*Reset)(struct Device * pDev); 
    int (*Start)(struct Device * pDev);
    int (*Stop)(struct Device * pDev);
    int (*DoWithCommand)(struct Device * pDev, void * inData, void * outData);
    
}Device;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void DeviceInit(Device * pDev);
void DeviceDeinit(Device * pDev);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Device_H__ */
