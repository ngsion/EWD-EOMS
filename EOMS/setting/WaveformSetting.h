//==============================================================================
//
// Title:		WaveformSetting.h
// Purpose:		A short description of the interface.
//
// Created on:	2023-03-16 at 17:19:51 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __WaveformSetting_H__
#define __WaveformSetting_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Setting.h"


//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct WaveformSetting
{
    Setting setting;
    int frequecy;
    double high;
    double low;
    double offset1;
    double offset2;

}WaveformSetting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void WaveformSettingInit(WaveformSetting * pSet);
void WaveformSettingDeinit(WaveformSetting * pSet);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __WaveformSetting_H__ */
