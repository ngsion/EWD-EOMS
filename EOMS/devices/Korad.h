//==============================================================================
//
// Title:		Korad.h
// Purpose:		A short description of the interface.
//
// Created on:	2024-05-05 at 21:11:21 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Korad_H__
#define __Korad_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Device.h"
 


//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct Korad
{
    Device device;

    
}Korad;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void KoradInit(Korad * pDev);
void KoradDeinit(Korad * pDev);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Korad_H__ */
