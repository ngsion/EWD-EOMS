//==============================================================================
//
// Title:		PicoammeterMeasure.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-19 at 10:56:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __PicoammeterMeasure_H__
#define __PicoammeterMeasure_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Measurement.h"

//==============================================================================
// Constants

#define PA_NAN_STR "+9.910000E+37"
#define PA_VAULE_KEY "I"

//==============================================================================
// Types

typedef struct PicoammeterMeasure
{
    Measurement measure;
    

}PicoammeterMeasure;


//==============================================================================
// External variables

//==============================================================================
// Global functions
void PicoammeterMeasureInit(PicoammeterMeasure * pMea);
void PicoammeterMeasureDeinit(PicoammeterMeasure * pMea);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __PicoammeterMeasure_H__ */
