//==============================================================================
//
// Title:		LCRSetting.h
// Purpose:		A short description of the interface.
//
// Created on:	2023-03-16 at 17:19:29 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __LCRSetting_H__
#define __LCRSetting_H__

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
typedef struct LCRSetting
{
    Setting setting;
    double VMax;
    double VMin;
    double VSpan;
    double MInterval;

}LCRSetting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void LCRSettingInit(LCRSetting * pSet);
void LCRSettingDeinit(LCRSetting * pSet);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LCRSetting_H__ */
