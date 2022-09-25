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

//==============================================================================
// Static functions
static int Init(int x)
{
	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{
		defaultMeasureArray[i] = NULL;
	}
	defaultMeasureArray[0] = malloc(sizeof(PicoammeterMeasure));
	PicoammeterMeasureInit((PicoammeterMeasure *)defaultMeasureArray[0]);
	defaultMeasureArray[0]->isCollector = false;

	defaultMeasureArray[1] = malloc(sizeof(LCRMeterMeasure));
	LCRMeterMeasureInit((LCRMeterMeasure *)defaultMeasureArray[1]);
	defaultMeasureArray[1]->isCollector = true;

	return 0;
}

static int Start(int x)
{
	for (int i = 0; i < MEASURE_MAX_NUM; i++)
	{

		if (NULL != defaultMeasureArray[i] && true == defaultMeasureArray[i]->isCollector)
		{
			LOG_INFO("before start");
			defaultMeasureArray[i]->Start(defaultMeasureArray[i]);
			LOG_INFO("after start");
		}
	}

	return 0;
}
static int Stop(int x)
{
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
