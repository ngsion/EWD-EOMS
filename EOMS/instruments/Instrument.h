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
    typedef  enum
    {
        Instrument_Status_Disconnected,
        Instrument_Status_Connected,
        Instrument_Status_Open
    } Instrument_Status;

    typedef struct
    {
        Instrument_Status status;
        uint32_t resouceMgr;
        char address[INSTRUMENT_ADDRESS_LENGTH];
        char id[INSTRUMENT_ID_LENGTH];

    } Instrument;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions

#ifdef __cplusplus
}
#endif

#endif /* ndef __Instrument_H__ */
