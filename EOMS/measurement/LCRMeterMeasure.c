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
static int DoMeasureWithCommand(struct Measurement *pMea, void *inData, void *outData1, void *outData2)
{

	int result = -1;
	if (NULL != pMea->pDev->pInstr && pMea->pDev->pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMea->pDev->pInstr->session;

		status = viPrintf(session, ":FETCh?\n");

		int num;
		unsigned char buffer[80];
		memset(buffer, 0, 80);
		ViUInt32 retCount = 0;
		status = viRead(session, buffer, 80, &retCount);
		if (status < VI_SUCCESS)
		{
			LOG_ERROR("Error reading a response from the device %d.", session);
		}
		else
		{
			double CpValue = 0.0;
			double DValue = 0.0;

			double *pOutValue = (double *)outData1;
			double *pDValue = (double *)outData2;
			LOG_INFO("instrument %d return %d is: %*s\n", session, retCount, retCount, buffer);
			char *p = NULL;
			p = strtok(buffer, ",");
			if (NULL != p)
			{
				num = Scan(p, "%s>%f", &CpValue);
				CpValue *= 1000000000000;
			}
			p = strtok(NULL, ",");
			if (NULL != p)
			{
				num = Scan(p, "%s>%f", &DValue);
			}
			p = strtok(NULL, ",");
			if (NULL != p)
			{
				num = Scan(p, "%s>%d", &result);
			}

			if (0 == result)
			{
				*pOutValue = CpValue;
				*pDValue = DValue;
				pMea->pDataQueue->Push(pMea->pDataQueue, *pOutValue);
				if (inData != NULL)
				{
					double *indat = (double *)inData;
					pMea->pInDataQueue->Push(pMea->pInDataQueue, *indat);
				}
			}
			LOG_INFO("num is %d , CpValue is %f DValue is %f queue size %d , inqueue size %d\n", num, CpValue, DValue, pMea->pDataQueue->size, pMea->pInDataQueue->size);
		}
	}
	else
	{
		LOG_ERROR("LCRMeterMeasure DoMeasureWithCommand failed null %d ", NULL == pMea->pDev->pInstr);
	}
	return result;
}

static int Start(Measurement *pMea)
{

	if (!pMea)
	{
		LOG_ERROR("error in LCRMeterMeasure start");
		return -1;
	}

	if (NULL != pMea->pDev->pInstr && pMea->pDev->pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("LCRMeterMeasure starts");
		ViStatus status;
		ViSession session = pMea->pDev->pInstr->session;
		status = viPrintf(session, "FUNC:IMP CPD\n");
		status = viPrintf(session, "FREQ 1kHz\n");
		status = viPrintf(session, "VOLT 0V\n");
		status = viPrintf(session, "APERture MED\n");
		status = viPrintf(session, "BIAS:VOLT 0\n");
		// status = viPrintf(session, "BIAS:STATE 0\n");
	}
	else
	{
		LOG_ERROR("LCRMeterMeasure Start failed null %d ", NULL == pMea->pDev->pInstr);
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
	pDev->measure.instrumentFlag = Instrument_LCRMeter;
	pDev->measure.Start = Start;
	pDev->measure.Stop = Stop;
	pDev->measure.DoMeasureWithCommand = DoMeasureWithCommand;
}
void LCRMeterMeasureDeinit(LCRMeterMeasure *pDev)
{
	pDev->measure.instrumentFlag = Instrument_LCRMeter;
	MeasurementDeinit(&pDev->measure);
}
