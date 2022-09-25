//==============================================================================
//
// Title:		PicoammeterMeasure.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-19 at 10:56:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <visa.h>
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include "PicoammeterMeasure.h"
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
	PicoammeterMeasure *pMeter = (PicoammeterMeasure *)pDev;

	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->measure.pInstr->session;
		double *pCurrent = (double *)outData;

		status = viPrintf(session, ":READ?\n");

		int num;
		double value;
		unsigned char buffer[14];
		memset(buffer, 0, 14);
		ViUInt32 retCount;
		status = viRead(session, buffer, 14, &retCount);
		if (status < VI_SUCCESS)
		{
			LOG_ERROR("Error reading a response from the device %d.", session);
		}
		else
		{

			num = Scan(buffer, "%s>%f", &value);
			*pCurrent = value * 1000000000;
			LOG_INFO("instrument %d num is %dreturn %d is: %*s\n", session, num, retCount,retCount, buffer);
			
		}
	}
	else
	{
		LOG_ERROR("Picoammeter DoMeasureWithCommand failed null %d ", NULL == pMeter->measure.pInstr);
	}
	return 0;
}

static int Start(Measurement *pDev)
{

	if (!pDev)
	{
		LOG_ERROR("error in PicoammeterMeasure start");
		return -1;
	}
	PicoammeterMeasure *pMeter = (PicoammeterMeasure *)pDev;
	 ViStatus status =  VI_SUCCESS;
	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("PicoammeterMeasure starts");
		
		ViSession session = pMeter->measure.pInstr->session;

		status = viPrintf(session, ":FORM:ELEM CURR1\n");
		status = viPrintf(session, ":SENS1:CURR:NPLC 1\n");
		status = viPrintf(session, ":SENS1:CURR:RANG:AUTO ON\n");
          


		// status = viPrintf(session, ":SYST:AZER OFF\n");
		// status = viPrintf(session, ":SENS1:MED OFF\n");
		// status = viPrintf(session, ":SENS1:AVERage OFF\n");
	}
	else
	{
		LOG_ERROR("PicoammeterMeasure Start failed null %d ", NULL == pMeter->measure.pInstr);
	}
	if (status < VI_SUCCESS)
	{
		LOG_ERROR("status is %d.", status);
	}
	return 0;
}
static int Stop(Measurement *pDev)
{
	LOG_INFO("PicoammeterMeasure Stops");

	return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions
//==============================================================================
// Global functions
void PicoammeterMeasureInit(PicoammeterMeasure *pDev)
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
void PicoammeterMeasureDeinit(PicoammeterMeasure *pDev)
{
	MeasurementDeinit(&pDev->measure);
}
