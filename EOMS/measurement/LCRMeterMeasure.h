//==============================================================================
//
// Title:		LCRMeterMeasure.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-09-24 at 21:18:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __LCRMeterMeasure_H__
#define __LCRMeterMeasure_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Measurement.h"
//==============================================================================
// Constants
#define LCR_NAN_STR "+9.90000E+37"

//==============================================================================
// Types
typedef struct LCRMeterMeasure
{
    Measurement measure;
    

}LCRMeterMeasure;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void LCRMeterMeasureInit(LCRMeterMeasure * pDev);
void LCRMeterMeasureDeinit(LCRMeterMeasure * pDev);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LCRMeterMeasure_H__ */
