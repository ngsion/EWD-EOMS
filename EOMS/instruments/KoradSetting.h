//==============================================================================
//
// Title:		KoradSetting.h
// Purpose:		A short description of the interface.
//
// Created on:	2024-05-05 at 21:25:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __KoradSetting_H__
#define __KoradSetting_H__

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

//==============================================================================
// External variables

//==============================================================================
// Global functions

typedef struct KoradSetting
{
    Setting setting;
 

}KoradSetting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void KoradSettingInit(KoradSetting * pSet);
void KoradSettingDeinit(KoradSetting * pSet);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __KoradSetting_H__ */
