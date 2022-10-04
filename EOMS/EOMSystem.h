//==============================================================================
//
// Title:		EOMSystem.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-16 at 11:22:05 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __EOMSystem_H__
#define __EOMSystem_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "logger.h"  
#include "instruments/InstrumentMgr.h"
#include "DeviceMgr.h"
#include "MeasurementMgr.h"
#include <stdbool.h>
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct 
{
	bool isWorking;

	int (*Init)(int x);
	int (*Shutdown)(int x);
	int (*LoadSettings)(int x);
    int (*Start)(int x);
	int (*Stop)(int x);
	
}EOMSystem;

//==============================================================================
// External variables
extern EOMSystem System;


//==============================================================================
// Global functions
		



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __EOMSystem_H__ */
