//==============================================================================
//
// Title:		MeasurementMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-18 at 15:36:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MeasurementMgr_H__
#define __MeasurementMgr_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Measurement.h"

//==============================================================================
// Constants
#define MEASURE_MAX_NUM 12

// Types
typedef struct MeasurementMgr
{
 
    Measurement ** pMeasureArray;
   
    int (*Init)(int x);
	int (*Start)(int x);
	int (*Stop)(int x);
	int (*Shutdown)(int x);

}MeasurementMgr;

//==============================================================================
// External variables

//==============================================================================
// Global functions


//==============================================================================
// External variables
extern MeasurementMgr MeasureMgr;


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MeasurementMgr_H__ */
