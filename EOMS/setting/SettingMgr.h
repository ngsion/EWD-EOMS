//==============================================================================
//
// Title:		SettingMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-04 at 21:10:43 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __SettingMgr_H__
#define __SettingMgr_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
typedef enum{
    Signal_None = 0,
    Signal_Picoammieter = 1 << 0,
    Signal_WaveformGenerator= 1 << 1,
    Signal_LCRMeter = 1 << 2,
    Signal_All = Signal_Picoammieter | Signal_WaveformGenerator | Signal_LCRMeter
};


typedef enum{
    Online_None = 0,
    Online_Picoammieter = 1 << 0,
    Online_WaveformGenerator= 1 << 1,
    Online_LCRMeter = 1 << 2,
    Online_Admesy = 1 << 3,
    Online_All = Signal_Picoammieter | Signal_WaveformGenerator | Signal_LCRMeter | Online_Admesy
};

typedef enum{
    Data_None = 0,
    Data_Current = 1 << 0,
    Data_Cp = 1 << 1,
    Data_D = 1 << 2,
    Data_ALL = Data_Current | Data_Cp | Data_D
};

//==============================================================================

// Types
typedef struct SettingMgr
{
    unsigned int signal;
    unsigned int data;
    unsigned int online;
    
    int (*Init)(int x);
	int (*Shutdown)(int x);

}SettingMgr;

//==============================================================================
// External variables

//==============================================================================
// Global functions


//==============================================================================
// External variables
extern SettingMgr SetMgr;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __SettingMgr_H__ */
