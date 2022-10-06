//==============================================================================
//
// Title:		Excel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-06 at 15:43:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <windows.h>
#include <ansi_c.h>
#include <utility.h>
#include "Excel.h"
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int SetCellInt(struct Excel *excel, char *key, int value)
{

}
static int SetCellStr(struct Excel *excel, char *key, char *value)
{
}
static int Save(struct Excel *excel)
{
    char NewRptFileName[128] = {0};
    time_t NowTime;
    time(&NowTime);
    struct tm *Now;
    Now = localtime(&NowTime);
    sprintf(NewRptFileName, "\\data\\report%04d%02d%02d-%02d%02d%02d.xls", Now->tm_year + 1900, Now->tm_mon + 1, Now->tm_mday, Now->tm_hour, Now->tm_min, Now->tm_sec);
    GetProjectDir(excel->ExcelFileName);
    strcat(excel->ExcelFileName, NewRptFileName);

    HRESULT result = ExcelRpt_WorkbookSave(excel->workbookHandle, excel->ExcelFileName, ExRConst_DefaultFileFormat);
    return result;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions

Excel *ExcelAllocInit()
{
    Excel *excel = (Excel *)malloc(sizeof(Excel));

    if (NULL != excel)
    {

        excel->SetCellInt = SetCellInt;
        excel->SetCellStr = SetCellStr;
        excel->Save = Save;
        excel->columnMap = MapAllocInit();
         excel->rowMap = MapAllocInit();
        

        HRESULT result = ExcelRpt_ApplicationNew(0, &(excel->applicationHandle));

        if (result < 0)
        {
            LOG_ERROR("ExcelRpt_ApplicationNew failed");
            return NULL;
        }
        result = ExcelRpt_WorkbookNew(excel->applicationHandle, &excel->workbookHandle);
        // ExcelRpt_WorkbookOpen(excel->applicationHandle, excel->ExcelFileName, &excel->workbookHandle);
        result = ExcelRpt_GetWorksheetFromName(excel->workbookHandle, "Sheet1", &(excel->worksheetHandle));
        result = ExcelRpt_ActivateWorksheet(excel->worksheetHandle);

        result = ExcelRpt_SetCellValue(excel->worksheetHandle, "C3", ExRConst_dataString, "afdsfds");
        result = ExcelRpt_SetCellValue(excel->worksheetHandle, "C4", ExRConst_dataString, "232132");
    }
    return excel;
}
void ExcelDelloc(Excel *excel)
{
    if (NULL != excel)
    {
        if (excel->worksheetHandle)
        {
            CA_DiscardObjHandle(excel->worksheetHandle);
        }

        if (excel->workbookHandle)
        {
            ExcelRpt_WorkbookClose(excel->workbookHandle, 0);
            CA_DiscardObjHandle(excel->workbookHandle);
        }

        if (excel->applicationHandle)
        {
            ExcelRpt_ApplicationQuit(excel->applicationHandle);
            CA_DiscardObjHandle(excel->applicationHandle);
        }
        free(excel->columnMap);
        free(excel->rowMap);
        free(excel);
        excel = NULL;
    }
}

void TestExel()
{
    Excel *pExel = ExcelAllocInit();
    pExel->Save(pExel);
    ExcelDelloc(pExel);
}
