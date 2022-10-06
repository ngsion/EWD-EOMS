//==============================================================================
//
// Title:		Excel.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-06 at 15:43:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Excel_H__
#define __Excel_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //==============================================================================
    // Include files
#include <windows.h>   
#include "excelreport.h"   
#include "cvidef.h"
#include "Map.h"


    // Types

    typedef struct Excel
    {
        CAObjHandle applicationHandle;
        CAObjHandle workbookHandle;
        CAObjHandle worksheetHandle;

        Map * columnMap;
        Map * rowMap;

		char ExcelFileName[MAX_PATHNAME_LEN];   
        int (*SetCellInt)(struct Excel *excel, char *key, int value);
        int (*SetCellStr)(struct Excel *excel, char *key, char *value);
        int (*Save)(struct Excel *excel);
    } Excel;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    Excel *ExcelAllocInit();
    void ExcelDelloc(Excel *excel);

    void TestExel();

#ifdef __cplusplus
}
#endif

#endif /* ndef __Excel_H__ */
