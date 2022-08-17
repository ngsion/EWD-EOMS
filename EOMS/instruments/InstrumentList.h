//==============================================================================
//
// Title:		InstrumentList.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-17 at 11:45:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __InstrumentList_H__
#define __InstrumentList_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Instrument.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct InstrumentListNode
{
    Instrument * pInstr;
    struct InstrumentListNode * next;
    
} InstrumentListNode;

//==============================================================================
// External variables

//==============================================================================
// Global functions

void InstrumentListAllocInit(InstrumentListNode ** plist,Instrument *pInstr);

void InstrumentListPushBack(InstrumentListNode ** plist, Instrument *pInstr);

void InstrumentListDelloc(InstrumentListNode ** plist);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __InstrumentList_H__ */
