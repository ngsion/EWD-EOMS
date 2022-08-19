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
#include "../instruments/Instrument.h"
//==============================================================================
// Constants
#define DEVICE_NAME_LENGTH 64
#define DEVICE_TITLE_LENGTH 64
//==============================================================================
// Types
typedef struct Device
{
    char  name[DEVICE_NAME_LENGTH];
    char  title[DEVICE_TITLE_LENGTH];
    Instrument * pInstr;
     
    int (*Start)(struct Device * pDev);
    int (*Stop)(struct Device * pDev);
    int (*DoFire)(struct Device * pDev, void * inData, void * outData);

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
