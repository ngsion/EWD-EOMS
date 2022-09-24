//==============================================================================
//
// Title:		EOMSystem.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 11:22:05 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include "EOMSystem.h"
#include "DeviceMgr.h"
#include "MeasurementMgr.h"
#include "logger.h"
#include <time.h>
#include <assert.h>
#include <string.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static FILE *fp = NULL;

void setupLogger()
{
	time_t now; // time_t
	time(&now);

	struct tm *tblock;
	tblock = localtime(&now);

	char buf[64] = {0};
	strftime(buf, 64, "log/EOMSlog_%Y%m%d_%H%M%S.txt", tblock);

	logger_initConsoleLogger(NULL);
	logger_initFileLogger(buf, 0, 0);
	logger_setLevel(LogLevel_DEBUG);
}

//==============================================================================
// Static functions
static int Init(int x)
{
	setupLogger();
	InstrMgr.Init(x);
	DevMgr.Init(x);
	MeasureMgr.Init(x);

	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		LOG_INFO("Init one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Open(pNode->pInstr);
		int i = 0;
		if (Instrument_Type_ASRL == pNode->pInstr->type)
		{
			for ( i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && 0 == strcmp(DevMgr.pDevArray[i]->name, DEVICE_PICOAMMETER_STR))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for ( i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && 0 == strcmp(MeasureMgr.pMeasureArray[i]->name, DEVICE_PICOAMMETER_STR))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
		}
		else if (Instrument_Type_USB == pNode->pInstr->type)
		{

			for ( i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && 0 == strcmp(DevMgr.pDevArray[i]->name, DEVICE_WAVEFORMGENTERATOR_STR))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for ( i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && 0 == strcmp(MeasureMgr.pMeasureArray[i]->name, DEVICE_WAVEFORMGENTERATOR_STR))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
		}
		else if (Instrument_Type_GPIB == pNode->pInstr->type)
		{
			for ( i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && 0 == strcmp(DevMgr.pDevArray[i]->name, DEVICE_LCRMETER_STR))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for ( i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && 0 == strcmp(MeasureMgr.pMeasureArray[i]->name, DEVICE_LCRMETER_STR))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
		}
		pHead = pNode->next;
	}

	DevMgr.AfterInit(x);
	return 0;
}
static int Shutdown(int x)
{
	if (NULL != fp)
	{
		// fclose(fp);
	}
	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		LOG_INFO("Shutdown one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Close(pNode->pInstr);
		pHead = pNode->next;
	}
	InstrMgr.Shutdown(x);
	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
	Device *pDev = ((Device *)(DevMgr.pDevArray[0]));
	Measurement *pMeasure = MeasureMgr.pMeasureArray[0];
	float max = 30;
	float min = 0;
	float step = 2;
	double current = 0.0;
	float volt;

	for (volt = min; volt <= max; volt += step)
	{
		LOG_INFO("before dowith command");
		pDev->DoWithCommand(pDev, &volt, NULL);
		LOG_INFO("after dowith command");

		Delay(0.01);
		pMeasure->DoMeasureWithCommand(pMeasure, &volt, &current);

		LOG_INFO("instrument  %d set volt %fV get current %fnA ", pDev->pInstr->session, volt, current);
	}

	return 0;
}

static int CVICALLBACK ThreadFunction2(void *functionData)
{

	Measurement *pMeasure = MeasureMgr.pMeasureArray[0]; 

	double current = 0.0;
	int volt;

	for (int i = 0; i < 100; i++)
	{
		LOG_INFO("before DoMeasureWithCommand");
		pMeasure->DoMeasureWithCommand(pMeasure, &volt, &current);
		LOG_INFO("instrument  %d  mesure %d get current %fnA ", pMeasure->pInstr->session, i, current);
		// Delay(0.1);
	}

	return 0;
}

static int Start(int x)
{
	DevMgr.Start(x);
	MeasureMgr.Start(x);

	int threadFunctionId = 0;

	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,
								  ThreadFunction, NULL,
								  &threadFunctionId);
	/* Wait for the thread functions to finish executing */
	CmtWaitForThreadPoolFunctionCompletion(DEFAULT_THREAD_POOL_HANDLE,
										   threadFunctionId,
										   0);

	/* Release thread functions */
	CmtReleaseThreadPoolFunctionID(DEFAULT_THREAD_POOL_HANDLE, threadFunctionId);

	return 0;
}
static int Stop(int x)
{
	MeasureMgr.Stop(x);
	DevMgr.Stop(x);

	return 0;
}

//==============================================================================
// Global variables
EOMSystem System = {
	.Init = Init,
	.Shutdown = Shutdown,
	.Start = Start,
	.Stop = Stop};

//==============================================================================
// Global functions
