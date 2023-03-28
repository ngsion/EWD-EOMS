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

#define COLUMN_START_POS 3
#define ROW_START_POS 3
#define MAX_COLUMN_COUNT 50
#define EXCEL_INFO_LEN  64
#define COLUMN_RECORD_SPAN 3

    // Types

    typedef struct Excel
    {
        CAObjHandle applicationHandle;
        CAObjHandle workbookHandle;
        CAObjHandle worksheetHandle;
     

        Map * columnMap;
        unsigned int currentColumnMax;
        unsigned int currentRowMax;
        unsigned int curretnStartRow;
        unsigned int recordCount;    
        char excelInfo[EXCEL_INFO_LEN];
		char excelFileName[MAX_PATHNAME_LEN];  

        int (*SetCell)(struct Excel *excel, char *key); //添加一个key
        int (*SetCellInt)(struct Excel *excel, char *key, int value);
        int (*SetCellDouble)(struct Excel *excel, char *key, double value);
        int (*SetCellStr)(struct Excel *excel, char *key, char *value);
        int (*Jump)(struct Excel *excel);
        int (*Save)(struct Excel *excel);
    } Excel;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    Excel *ExcelAllocInit(const char * info);
    void ExcelDelloc(Excel *excel);

    void TestExel();

#ifdef __cplusplus
}
#endif

#endif /* ndef __Excel_H__ */
