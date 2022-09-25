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
	defaultMeasureArray[0]->isCollector = true;

	defaultMeasureArray[1] = malloc(sizeof(LCRMeterMeasure));
	LCRMeterMeasureInit((LCRMeterMeasure *)defaultMeasureArray[1]);
	defaultMeasureArray[1]->isCollector = true;

	return 0;
}

static int CVICALLBACK ThreadFunction2(void *functionData)
{
	Measurement *pMeasure = (Measurement *)functionData;
	while (true == isCollecting)
	{
		double value;
		LOG_INFO("before mesure");
		pMeasure->DoMeasureWithCommand(pMeasure, NULL, &value);
		LOG_INFO("after mesure value %f", value);
	
		Delay(0.001);
	}

	return 0;
}

static int DoOneMeasure(Measurement *pMeasure)
{

	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,
								  ThreadFunction2, pMeasure,
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

//==============================================================================
// Global functions

//==============================================================================
// Global variables

MeasurementMgr MeasureMgr = {
	.pMeasureArray = &defaultMeasureArray,
	.Init = Init,
	.Start = Start,
	.Stop = Stop,
	.Shutdown = Shutdown};
