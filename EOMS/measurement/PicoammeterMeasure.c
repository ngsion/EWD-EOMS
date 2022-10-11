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
static int DoMeasureWithCommand(struct Measurement *pDev, void *inData, void *outData1, void *outData2)
{
	PicoammeterMeasure *pMeter = (PicoammeterMeasure *)pDev;

	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->measure.pInstr->session;
		double *pOutValue = (double *)outData1;

		status = viPrintf(session, ":READ?\n");

		int num;
		double value;
		unsigned char buffer[14] = {0};
		memset(buffer, 0, 14);
		ViUInt32 retCount;
		status = viRead(session, buffer, 14, &retCount);
		if (status < VI_SUCCESS)
		{
			LOG_ERROR("Error reading a response from the device %d.", session);
		}
		else
		{
			// if (0 ==  strcmp(buffer,PA_NAN_STR))
			{
				//	return -1;
			}
			buffer[13] = '\0';
			num = Scan(buffer, "%s>%f", &value);
			value *= 1000000000; /// A -> NA
			LOG_INFO("instrument %d num is %d value is %f,return %d is: %*s\n", session, num, value, retCount, retCount, buffer);
			*pOutValue = value;
			if (inData != NULL)
			{
				double *indat = (double *)inData;
				pDev->pInDataQueue->Push(pDev->pInDataQueue, *indat);
			}
			pDev->pDataQueue->Push(pDev->pDataQueue, *pOutValue);
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
	ViStatus status = VI_SUCCESS;
	if (NULL != pMeter->measure.pInstr && pMeter->measure.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("PicoammeterMeasure starts");

		ViSession session = pMeter->measure.pInstr->session;

		status = viPrintf(session, ":FORM:ELEM CURR1\n");
		// status = viPrintf(session, ":SENS1:CURR:NPLC 1\n");
		status = viPrintf(session, ":SENS1:CURR:RANG:AUTO ON\n");
		//  status = viPrintf(session, ":CONFIgure:CURRent:DC\n");
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
	pDev->measure.instrumentFlag = Instrument_Picoammeter;
	pDev->measure.Start = Start;
	pDev->measure.Stop = Stop;
	pDev->measure.DoMeasureWithCommand = DoMeasureWithCommand;
}
void PicoammeterMeasureDeinit(PicoammeterMeasure *pDev)
{
	MeasurementDeinit(&pDev->measure);
}
