//==============================================================================
//
// Title:		Measurement.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-18 at 15:35:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Measurement_H__
#define __Measurement_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Instrument.h"
#include <stdbool.h>


//==============================================================================
// Constants
#define kDEVICE_NAME_LENGTH 64
#define kDEVICE_PICOAMMETER_STR "Picoammeter"
#define kDEVICE_WAVEFORMGENTERATOR_STR "WaveformGenerator"
#define kDEVICE_LCRMETER_STR "LCRMeter"

//==============================================================================
// Types
typedef struct Measurement
{
    Instrument * pInstr;
    char  name[kDEVICE_NAME_LENGTH];
    bool isCollector;
     
    int (*Start)(struct Measurement * pDev);
    int (*Stop)(struct Measurement * pDev);
    int (*DoMeasureWithCommand)(struct Measurement * pDev, void * inData, void * outData);

}Measurement;

//==============================================================================
// External variables

//==============================================================================
// Global functions
void MeasurementInit(Measurement * pDev);
void MeasurementDeinit(Measurement * pDev);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Measurement_H__ */
