//==============================================================================
//
// Title:		DataSaveMgr.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-06 at 21:29:27 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __DataSaveMgr_H__
#define __DataSaveMgr_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //==============================================================================
    // Include files
#include "Excel.h"  
#include "cvidef.h"


    //==============================================================================
    // Constants

    typedef struct DataSaveMgr
    {

        int (*Start)(int x);
        int (*Stop)(int x);
        int (*SaveInt)(char *key, int value);
        int (*SaveDouble)(char *key, double value);
        int (*SaveStr)(char *key, char *value);

    } DataSaveMgr;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions

    //==============================================================================
    // External variables
    extern DataSaveMgr DataMgr;

#ifdef __cplusplus
}
#endif

#endif /* ndef __DataSaveMgr_H__ */
