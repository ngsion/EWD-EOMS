//==============================================================================
//
// Title:		WaveformGenerator.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-09-15 at 17:36:30 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __WaveformGenerator_H__
#define __WaveformGenerator_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //==============================================================================
    // Include files

#include "cvidef.h"
#include "Device.h"
#include "WaveformSetting.h"
    //==============================================================================
    // Constants

    //==============================================================================
    // Types
    typedef struct WaveformGenerator
    {
        Device device;

        WaveformSetting *pSetting;

    } WaveformGenerator;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    void WaveformGeneratorInit(WaveformGenerator *pDev);
    void WaveformGeneratorDeinit(WaveformGenerator *pDev);

#ifdef __cplusplus
}
#endif

#endif /* ndef __WaveformGenerator_H__ */
