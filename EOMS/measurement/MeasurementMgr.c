//==============================================================================
//
// Title:		MeasurementMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 15:36:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "DataSaveMgr.h"     
#include <utility.h>
#include <ansi_c.h>
#include "MeasurementMgr.h"
#include "PicoammeterMeasure.h"
#include "LCRMeterMeasure.h"
#include "logger.h"


//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static Measurement *defaultMeasureArray[MEASURE_MAX_NUM];

static bool isCollecting;

//==============================================================================
// Static functions
static int Init(int x)
{
	isCollecting = false;
	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		defaultMeasureArray[i] = NULL;
	}
	defaultMeasureArray[0] = malloc(sizeof(PicoammeterMeasure));
	PicoammeterMeasureInit((PicoammeterMeasure *)defaultMeasureArray[0]);


	defaultMeasureArray[1] = malloc(sizeof(LCRMeterMeasure));
	LCRMeterMeasureInit((LCRMeterMeasure *)defaultMeasureArray[1]);

	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
	Measurement *pMeasure = (Measurement *)functionData;
	while (true == isCollecting)
	{
		double value = 0;
		double dvalue = 0;
		LOG_INFO("before mesure");
		if (0 == pMeasure->DoMeasureWithCommand(pMeasure, &dvalue, &value))
		{
			if(pMeasure->instrumentFlag == Instrument_Picoammeter)
			{
				DataMgr.SaveDouble("I", value);
			}
			else if(pMeasure->instrumentFlag == Instrument_LCRMeter)
			{
				DataMgr.SaveDouble("C", value);
				DataMgr.SaveDouble("D", dvalue);
			}
			LOG_INFO("after mesure value %f", value);
		}
		else
		{
			LOG_INFO("DoMeasureWithCommand return invalid value");
		}

	//	Delay(0.1);
	}

	return 0;
}

static int DoOneMeasure(Measurement *pMeasure)
{

	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,
								  ThreadFunction, pMeasure,
								  &pMeasure->jobId);
	return 0;
}

static int Start(int x)
{
	isCollecting = true;

	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		if (NULL != defaultMeasureArray[i] && true == defaultMeasureArray[i]->isCollector)
		{
			LOG_INFO("before start");
			defaultMeasureArray[i]->Start(defaultMeasureArray[i]);
			LOG_INFO("after start");
			DoOneMeasure(defaultMeasureArray[i]);
		}
	}

	return 0;
}
static int Stop(int x)
{
	if (true == isCollecting)
	{
		isCollecting = false;

		for (int i = 0; i < MEASURE_MAX_NUM; i++)
		{
			if (NULL != defaultMeasureArray[i] && true == defaultMeasureArray[i]->isCollector)
			{
				/* Wait for the thread functions to finish executing */
				CmtWaitForThreadPoolFunctionCompletion(DEFAULT_THREAD_POOL_HANDLE,
													   defaultMeasureArray[i]->jobId,
													   0);
				/* Release thread functions */
				CmtReleaseThreadPoolFunctionID(DEFAULT_THREAD_POOL_HANDLE, defaultMeasureArray[i]->jobId);
			}
		}
	}

	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		if (NULL != defaultMeasureArray[i] && true == defaultMeasureArray[i]->isCollector)
		{
			defaultMeasureArray[i]->Stop(defaultMeasureArray[i]);
		}
	}

	return 0;
}
static int Shutdown(int x)
{
	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		if (NULL != defaultMeasureArray[i])
		{
			free(defaultMeasureArray[i]);
			defaultMeasureArray[i] = NULL;
		}
	}

	return 0;
}

static Measurement *FindWithInstrFlag(int flag)
{
	Measurement *pMeter = NULL;
	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		if (NULL != defaultMeasureArray[i] && (defaultMeasureArray[i]->instrumentFlag == flag))
		{
			pMeter = defaultMeasureArray[i];
			break;
		}
	}
	return pMeter;
}

//==============================================================================
// Global functions

//==============================================================================
// Global variables

MeasurementMgr MeasureMgr = {
	.pMeasureArray = &defaultMeasureArray,
	.Init = Init,
	.Start = Start,
	.Stop = Stop,
	.Shutdown = Shutdown,
	.FindWithInstrFlag = FindWithInstrFlag
	
	};
