//==============================================================================
//
// Title:		AdmesySetting.h
// Purpose:		A short description of the interface.
//
// Created on:	2023-03-17 at 21:11:33 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __AdmesySetting_H__
#define __AdmesySetting_H__

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
typedef struct AdmesySetting
{
    Setting setting;

}AdmesySetting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void AdmesySettingInit(AdmesySetting * pSet);
void AdmesySettingDeinit(AdmesySetting * pSet);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AdmesySetting_H__ */
