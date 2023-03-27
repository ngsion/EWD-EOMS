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
static Excel *fileArray[MAX_FILE_COUNT];

// Static functions

static int Init(int x)
{
	for (int index = 0; index < MAX_FILE_COUNT; index++)
	{
		fileArray[index] = NULL;
	}

	return 0;
}
static Excel *GetOneWithInfo(const char *info)
{
	if (!info)
	{
		LOG_ERROR("GetOneWithInfo info is  NULL ");
		return NULL;
	}

	int index = 0;

	for (index = 0; index < MAX_FILE_COUNT; index++)
	{
		if (NULL != fileArray[index] && 0 == strcmp(info, fileArray[index]->excelInfo))
		{
			return fileArray[index];
		}
	}

	for (index = 0; index < MAX_FILE_COUNT; index++)
	{
		if (NULL == fileArray[index])
		{
			fileArray[index] = ExcelAllocInit(info);
			return fileArray[index];
		}
	}
	LOG_ERROR("GetOneWithInfo too much files ");
	return NULL;
}

static int Sync(Excel *pfile)
{
	if (NULL != pfile)
	{
		for (int index = 0; index < MAX_FILE_COUNT; index++)
		{
			if (pfile == fileArray[index])
			{
				pfile->Save(pfile);
				ExcelDelloc(pfile);
				fileArray[index] = NULL;
				return 0;
			}
		}
	}

	return 0;
}

static int Shutdown(int x)
{
	for (int index = 0; index < MAX_FILE_COUNT; index++)
	{
		if (NULL != fileArray[index])
		{
			fileArray[index]->Save(fileArray[index]);
			ExcelDelloc(fileArray[index]);
			fileArray[index] = NULL;
		}
	}

	return 0;
}

static int SaveKey(Excel *pfile, char *key)
{
	if (NULL != pfile)
	{
		pfile->SetCell(pfile, key);
	}
	else
	{
		LOG_ERROR("SaveKey Failed , %s", key);
	}
	return 0;
}
static int SaveInt(Excel *pfile, char *key, int value)
{
	if (NULL != pfile)
	{
		pfile->SetCellInt(pfile, key, value);
	}
	else
	{
		LOG_ERROR("SaveInt Failed , %s, %d", key, value);
	}
	return 0;
}
static int SaveDouble(Excel *pfile, char *key, double value)
{
	if (NULL != pfile)
	{
		pfile->SetCellDouble(pfile, key, value);
	}
	else
	{
		LOG_ERROR("SaveDouble Failed , %s, %f", key, value);
	}
	return 0;
}
static int SaveStr(Excel *pfile, char *key, char *value)
{
	if (NULL != pfile)
	{
		pfile->SetCellStr(pfile, key, value);
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
	.GetOneWithInfo = GetOneWithInfo,
	.Init = Init,
	.Shutdown = Shutdown,
	.Sync = Sync,
	.SaveKey = SaveKey,
	.SaveInt = SaveInt,
	.SaveDouble = SaveDouble,
	.SaveStr = SaveStr};
