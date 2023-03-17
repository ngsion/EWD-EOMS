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
#include "Setting.h"

//==============================================================================
// Constants

#define SETTING_MAX_NUM 12

//==============================================================================

// Types
typedef struct SettingMgr
{
   
    int (*Init)(int x);
	int (*Shutdown)(int x);
    Setting * (*FindWithInstrFlag)(int flag);

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
