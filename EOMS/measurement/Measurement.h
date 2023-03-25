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
#include "Device.h"
#include <stdbool.h>
#include "Queue.h"
#include "Setting.h"

//==============================================================================
// Constants



//==============================================================================
// Types
typedef struct Measurement
{
    
    unsigned int instrumentFlag;
   
    Device * pDev;
    Setting * pSet;


    Queue * pInDataQueue;
    Queue * pDataQueue;
    bool isCollecting;
    


    int (*Start)(struct Measurement * pMea);
    int (*Stop)(struct Measurement * pMea);
    int (*DoMeasureWithCommand)(struct Measurement * pMea, void * inData, void * outData1, void * outData2);

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
