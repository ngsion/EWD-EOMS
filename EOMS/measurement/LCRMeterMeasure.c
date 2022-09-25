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
#include <string.h>

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
		
        status = viPrintf(session, ":FETCh?\n");

		int num;
		unsigned char buffer[80];
		memset(buffer, 0, 80);
		ViUInt32 retCount;
		status = viRead(session, buffer, 80, &retCount);
		if (status < VI_SUCCESS)
		{
			LOG_ERROR("Error reading a response from the device %d.", session);
		}
		else
		{
			double CpValue = 0.0;
			double DValue = 0.0;
            double * pOutValue = (double*)outData;
			LOG_INFO("instrument %d return %d is: %*s\n", session, retCount,retCount, buffer);
			char * p = NULL;
			p = strtok(buffer,",");
			if (NULL != p)
			{
				 num = Scan(p, "%s>%f", &CpValue);
				 CpValue *= 1000000000;
			}
			p = strtok(NULL,",");
			if (NULL != p)
			{
				 num = Scan(p, "%s>%f", &DValue);
			}
			LOG_INFO("num is %d , CpValue is %f DValue is %f\n",num, CpValue, DValue);
			*pOutValue = CpValue;
		}
	
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
	memcpy(pDev->measure.name, kDEVICE_LCRMETER_STR, sizeof(kDEVICE_LCRMETER_STR));
	pDev->measure.Start = Start;
	pDev->measure.Stop = Stop;
	pDev->measure.DoMeasureWithCommand = DoMeasureWithCommand;
}
void LCRMeterMeasureDeinit(LCRMeterMeasure *pDev)
{
	MeasurementDeinit(&pDev->measure);
}

