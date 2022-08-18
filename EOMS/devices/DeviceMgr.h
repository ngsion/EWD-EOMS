//==============================================================================
//
// Title:		DeviceMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-18 at 13:42:24 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __DeviceMgr_H__
#define __DeviceMgr_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Device.h"

//==============================================================================
// Constants
#define DEVICE_MAX_NUM 12

//==============================================================================
// Types
typedef struct DeviceMgr
{
    Device ** pDevArray;
	int (*Init)(int x);
    int (*AfterInit)(int x);
	int (*Start)(int x);
	int (*Stop)(int x);
	int (*Shutdown)(int x);

}DeviceMgr;

//==============================================================================
// External variables

//==============================================================================
// Global functions


//==============================================================================
// External variables
extern DeviceMgr DevMgr;


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DeviceMgr_H__ */
