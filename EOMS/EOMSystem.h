//==============================================================================
//
// Title:		EOMSystem.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-16 at 11:22:05 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __EOMSystem_H__
#define __EOMSystem_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "logger/log.h"  

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
		
		
typedef struct 
{
	
	int (*Init)(int x);
	int (*Shutdown)(int x);
	
}EOMSystem;

extern EOMSystem System;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __EOMSystem_H__ */
