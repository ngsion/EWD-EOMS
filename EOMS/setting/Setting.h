//==============================================================================
//
// Title:		Setting.h
// Purpose:		A short description of the interface.
//
// Created on:	2023-03-16 at 16:58:54 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Setter_H__
#define __Setter_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include "cvidef.h"
#include <stdbool.h>
#include "Instrument.h"
//==============================================================================
// Constants



//==============================================================================
// Types
typedef struct Setting
{
    unsigned int instrumentFlag;
    bool isSignal;
    bool isColector;


    int (*Start)(struct Setting * pSet);
    int (*Stop)(struct Setting * pSet);

}Setting;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void SetterInit(Setting * pSet);
void SetterDeinit(Setting * pSet);



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Setter_H__ */
