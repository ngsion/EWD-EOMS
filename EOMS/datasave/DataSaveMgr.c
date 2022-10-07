//==============================================================================
//
// Title:		DataSaveMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-06 at 21:29:27 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "DataSaveMgr.h"
#include "logger.h"

//==============================================================================
// Constants
static Excel *psExcel;
// Static functions

static int Start(int x)
{
	if (NULL == psExcel)
	{
		psExcel = ExcelAllocInit();
	}

	return 0;
}
static int Stop(int x)
{
	if (NULL != psExcel)
	{
		psExcel->Save(psExcel);
		ExcelDelloc(psExcel);
		psExcel = NULL;
	}

	return 0;
}

static int SaveKey(char *key)
{
	if (NULL != psExcel)
	{
		psExcel->SetCell(psExcel, key);
	}
	else
	{
		LOG_ERROR("SaveKey Failed , %s", key);
	}
	return 0;
}
static int SaveInt(char *key, int value)
{
	if (NULL != psExcel)
	{
		psExcel->SetCellInt(psExcel, key, value);
	}
	else
	{
		LOG_ERROR("SaveInt Failed , %s, %d", key, value);
	}
	return 0;
}
static int SaveDouble(char *key, double value)
{
	if (NULL != psExcel)
	{
		psExcel->SetCellDouble(psExcel, key, value);
	}
	else
	{
		LOG_ERROR("SaveDouble Failed , %s, %f", key, value);
	}
	return 0;
}
static int SaveStr(char *key, char *value)
{
	if (NULL != psExcel)
	{
		psExcel->SetCellStr(psExcel, key, value);
	}
	else
	{
		LOG_ERROR("SetCellStr Failed , %s, %s", key, value);
	}
	return 0;
}
//==============================================================================
// Global variables

DataSaveMgr DataMgr = {
	.Start = Start,
	.Stop = Stop,
	.SaveKey = SaveKey,
	.SaveInt = SaveInt,
	.SaveDouble = SaveDouble,
	.SaveStr = SaveStr};
