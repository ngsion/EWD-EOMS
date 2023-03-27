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
    
    #define MAX_FILE_COUNT 32

    typedef struct DataSaveMgr
    {
        Excel * (*GetOneWithInfo)(const char * info);
        int (*Start)(int x);
        int (*Stop)(int x);
        int (*Sync)(int x);
        int (*SaveKey)(Excel * pfile, char *key);
        int (*SaveInt)(Excel * pfile, char *key, int value);
        int (*SaveDouble)(Excel * pfile, char *key, double value);
        int (*SaveStr)(Excel * pfile, char *key, char *value);

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
