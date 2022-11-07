//==============================================================================
//
// Title:		Instrument.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-08-16 at 14:05:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Instrument_H__
#define __Instrument_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //==============================================================================
    // Include files

#include "cvidef.h"
#include <stdint.h>


//==============================================================================
// Constants
#define INSTRUMENT_ID_LENGTH 128
#define INSTRUMENT_ADDRESS_LENGTH 256

    //==============================================================================
    // Types

typedef enum{
    Instrument_Unknown = 0,
    Instrument_Picoammeter = 1,
    Instrument_LCRMeter,
    Instrument_WaveformGenerator,
    Instrument_Admesy
};

    typedef enum
    {
        Instrument_Status_Disconnected = 0,
        Instrument_Status_Connected,
        Instrument_Status_Open
    } Instrument_Status;

    typedef enum
    {
        Instrument_Type_UNKNOWN = 0,
        Instrument_Type_GPIB,
        Instrument_Type_VXI,
        Instrument_Type_GPIB_VXI,
        Instrument_Type_ASRL,
        Instrument_Type_PXI,
        Instrument_Type_TCPIP,
        Instrument_Type_USB,

    }Instrument_Type;

    typedef struct Instrument
    {
        Instrument_Status status;
        Instrument_Type type;
        uint32_t resouceMgr;
        uint32_t session;
        char address[INSTRUMENT_ADDRESS_LENGTH];
        char identifier[INSTRUMENT_ID_LENGTH];

  
        int (*Open)(struct Instrument *pInstr);
        int (*QueryID)(struct Instrument *pInstr);
        int (*Close)(struct Instrument *pInstr);

    } Instrument;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    Instrument * InstrumentAllocInit();
    void InstrumentDelloc(Instrument * pInstr);

#ifdef __cplusplus
}
#endif

#endif /* ndef __Instrument_H__ */
