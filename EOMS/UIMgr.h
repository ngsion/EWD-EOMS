//==============================================================================
//
// Title:		UIMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-09 at 21:50:02 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __UIMgr_H__
#define __UIMgr_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
typedef struct 
{

	int (*ShowEntry)(int x);
	int (*ShowGraph)(int x);
    int (*ShowLCGraph)(int x);
	
}UIMgr;

//==============================================================================
// External variables
extern UIMgr UI;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __UIMgr_H__ */
