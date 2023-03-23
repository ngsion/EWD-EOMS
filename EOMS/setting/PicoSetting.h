//==============================================================================
//
// Title:		PicoSetting.h
// Purpose:		A short description of the interface.
//
// Created on:	2023-03-16 at 17:11:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __PicoSetting_H__
#define __PicoSetting_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Setting.h"


//==============================================================================
// Constants
#define BATCH_NO_LENGTH 64

//==============================================================================
// Types
typedef struct PicoSetting
{
    Setting setting;
    double VMax;
    double VMin;
    double VSpan;
    double MInterval;
  

}PicoSetting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void PicoSettingInit(PicoSetting * pSet);
void PicoSettingDeinit(PicoSetting * pSet);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __PicoSetting_H__ */
