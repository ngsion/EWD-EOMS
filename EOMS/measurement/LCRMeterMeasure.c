//==============================================================================
//
// Title:		LCRMeterMeasure.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-09-24 at 21:18:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LCRMeterMeasure.h"
#include <visa.h>
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables


//==============================================================================
// Static functions
static int DoMeasureWithCommand(struct Measurement *pDev, void *inData, void *outData)
{
	LCRMeterMeasure *pMeter = (LCRMeterMeasure *)pDev;

	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->measure.pInstr->session;
		double *pCurrent = (double *)outData;

	
	}
	else
	{
		LOG_ERROR("LCRMeterMeasure DoMeasureWithCommand failed null %d ", NULL == pMeter->measure.pInstr);
	}
	return 0;
}


static int Start(Measurement *pDev)
{

	if (!pDev)
	{
		LOG_ERROR("error in LCRMeterMeasure start");
		return -1;
	}
	LCRMeterMeasure *pMeter = (LCRMeterMeasure *)pDev;

	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("LCRMeterMeasure starts");
		ViStatus status;
		ViSession session = pMeter->measure.pInstr->session;
	
		
	}
	else
	{
		LOG_ERROR("LCRMeterMeasure Start failed null %d ", NULL == pMeter->measure.pInstr);
	}

	return 0;
}
static int Stop(Measurement *pDev)
{
	LOG_INFO("LCRMeterMeasure Stops");

	return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions
//==============================================================================
// Global functions
void LCRMeterMeasureInit(LCRMeterMeasure *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	MeasurementInit(&pDev->measure);
	memcpy(pDev->measure.name, kDEVICE_PICOAMMETER_STR, sizeof(kDEVICE_PICOAMMETER_STR));
	pDev->measure.Start = Start;
	pDev->measure.Stop = Stop;
	pDev->measure.DoMeasureWithCommand = DoMeasureWithCommand;
}
void LCRMeterMeasureDeinit(LCRMeterMeasure *pDev)
{
	MeasurementDeinit(&pDev->measure);
}

