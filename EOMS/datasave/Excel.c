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
static int Save(struct Excel *excel)
{

    HRESULT result = ExcelRpt_WorkbookSave(excel->workbookHandle, excel->excelFileName, ExRConst_DefaultFileFormat);
    return (result < 0) ? -1 : 0;
}

static int Jump(struct Excel *excel)
{
   excel->currentColumnMax += COLUMN_RECOR_SPAN;
  
    return  0;
}

/// 获取key这列数据最新的位置，若没有这个key，则添加之
static int GetIndex(struct Excel *excel, char *key, unsigned int *cvalue, unsigned int *rvalue)
{
    char index[8] = {0};

    if (-1 == excel->columnMap->GetValue(excel->columnMap, key, cvalue, rvalue))
    {
        excel->columnMap->SetMap(excel->columnMap, key, excel->currentColumnMax, ROW_START_POS);
        sprintf(index, "%c%d", 64 + excel->currentColumnMax, ROW_START_POS);
        ExcelRpt_SetCellValue(excel->worksheetHandle, index, ExRConst_dataString, key);
        ++excel->currentColumnMax;
    }
    return excel->columnMap->GetValue(excel->columnMap, key, cvalue, rvalue);
}

static int SetCell(struct Excel *excel, char *key)
{
    unsigned int column = 0;
    unsigned int row = 0;
    return GetIndex(excel, key, &column, &row);
}
static int SetCellInt(struct Excel *excel, char *key, int value)
{
    char index[8] = {0};
    unsigned int column = 0;
    unsigned int row = 0;

    if (0 == GetIndex(excel, key, &column, &row))
    {
        ++row;
        excel->columnMap->SetMap(excel->columnMap, key, column, row);
        sprintf(index, "%c%d", 64 + column, row);
        ExcelRpt_SetCellValue(excel->worksheetHandle, index, ExRConst_dataInt, value);
        //if (++excel->recordCount > MAX_SYNC_COUNT)
          //  excel->Save(excel);
    }
    else
    {
        LOG_ERROR("SetCellInt failed");
    }
    return 0;
}

static int SetCellDouble(struct Excel *excel, char *key, double value)
{
    char index[8] = {0};
    unsigned int column = 0;
    unsigned int row = 0;
    if (0 == GetIndex(excel, key, &column, &row))
    {
        ++row;
        excel->columnMap->SetMap(excel->columnMap, key, column, row);
        sprintf(index, "%c%d", 64 + column, row);
        ExcelRpt_SetCellValue(excel->worksheetHandle, index, ExRConst_dataDouble, value);
       // if (++excel->recordCount > MAX_SYNC_COUNT)
          //  excel->Save(excel);
    }
    else
    {
        LOG_ERROR("SetCellDouble failed");
    }
    return 0;
}
static int SetCellStr(struct Excel *excel, char *key, char *value)
{
    char index[8] = {0};
    unsigned int column = 0;
    unsigned int row = 0;
    if (0 == GetIndex(excel, key, &column, &row))
    {
        ++row;
        excel->columnMap->SetMap(excel->columnMap, key, column, row);
        sprintf(index, "%c%d", 65 + column, row);
        ExcelRpt_SetCellValue(excel->worksheetHandle, index, ExRConst_dataString, value);
       // if (++excel->recordCount > MAX_SYNC_COUNT)
           // excel->Save(excel);
    }
    else
    {
        LOG_ERROR("SetCellStr failed");
    }
    return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions

Excel *ExcelAllocInit(const char *info)
{
    Excel *excel = (Excel *)malloc(sizeof(Excel));

    if (NULL != excel)
    {

        memset(excel->excelInfo, 0, EXCEL_INFO_LEN);
        memcpy(excel->excelInfo, info, strlen(info));

        memset(excel->excelFileName, 0, MAX_PATHNAME_LEN);
        GetProjectDir(excel->excelFileName);

        char fileName[MAX_PATHNAME_LEN] = {0};
        time_t NowTime;
        time(&NowTime);
        struct tm *Now;
        Now = localtime(&NowTime);
        sprintf(fileName, "\\data\\%s-%04d%02d%02d.xls", info, Now->tm_year + 1900, Now->tm_mon + 1, Now->tm_mday);

        strcat(excel->excelFileName, fileName);

        excel->SetCell = SetCell;
        excel->SetCellInt = SetCellInt;
        excel->SetCellStr = SetCellStr;
        excel->Save = Save;
        excel->Jump = Jump;
        excel->SetCellDouble = SetCellDouble;
        excel->columnMap = MapAllocInit();
        excel->currentColumnMax = COLUMN_START_POS;
        excel->recordCount = 0;

        HRESULT result = ExcelRpt_ApplicationNew(0, &(excel->applicationHandle));

        if (result < 0)
        {
            LOG_ERROR("ExcelRpt_ApplicationNew failed");
            return NULL;
        }
       
        result = ExcelRpt_WorkbookOpen(excel->applicationHandle, excel->excelFileName, &excel->workbookHandle);
        if (result < 0)
        {
             result = ExcelRpt_WorkbookNew(excel->applicationHandle, &excel->workbookHandle);
        }
        result = ExcelRpt_GetWorksheetFromName(excel->workbookHandle, "Sheet1", &(excel->worksheetHandle));
        result = ExcelRpt_ActivateWorksheet(excel->worksheetHandle);


        char timestamp[32] = {0};
        sprintf(timestamp, "%02d:%02d:%02d",Now->tm_hour, Now->tm_min, Now->tm_sec);
        excel->SetCellStr(excel,"timestamp",timestamp); //记录时间戳
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
        free(excel);
        excel = NULL;
    }
}

void TestExel()
{
    Excel *pExel = ExcelAllocInit("oio");
    Excel *pExel2 = ExcelAllocInit("767");
    pExel2->SetCellInt(pExel, "V", 10);
    pExel->SetCellInt(pExel, "V", 10);
    pExel->SetCellDouble(pExel, "V", 10.9);
    pExel->SetCellStr(pExel, "V1", "11.9");
    pExel->SetCellDouble(pExel, "V1", 20.9);
    pExel->SetCellInt(pExel, "V3", 17);
    pExel->SetCellDouble(pExel, "V3", 70);
    pExel->SetCellDouble(pExel, "V3", 70);
    pExel->Save(pExel);
    ExcelDelloc(pExel);
    Delay(1);
    pExel2->Save(pExel2);
    ExcelDelloc(pExel2);
}
