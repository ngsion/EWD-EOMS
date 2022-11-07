//==============================================================================
//
// Title:		InstrumentMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-16 at 15:07:11 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __InstrumentMgr_H__
#define __InstrumentMgr_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "InstrumentList.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct InstrumentMgr
{
	InstrumentListNode ** plist;

	int (*Init)(int x);
	int (*Open)(struct InstrumentMgr * pMgr);
	int (*QueryID)(struct InstrumentMgr * pMgr);
	int (*Shutdown)(int x);
	
	
}InstrumentMgr;

//==============================================================================
// External variables
extern InstrumentMgr InstrMgr;

//==============================================================================
// Global functions



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __InstrumentMgr_H__ */
