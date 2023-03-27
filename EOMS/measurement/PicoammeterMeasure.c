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
#include "DataSaveMgr.h"
#include <visa.h>
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include "PicoammeterMeasure.h"
#include "logger.h"
#include "PicoSetting.h"
#include "Stack.h"

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

	if (NULL != pMea->pDev->pInstr && pMea->pDev->pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMea->pDev->pInstr->session;
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
				pMea->pInDataQueue->Push(pMea->pInDataQueue, *indat);
			}
			pMea->pDataQueue->Push(pMea->pDataQueue, *pOutValue);
		}
	}
	else
	{
		LOG_ERROR("Picoammeter DoMeasureWithCommand failed null %d ", NULL == pMea->pDev->pInstr);
	}
	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
	Measurement *pMeasure = (Measurement *)functionData;
	Device *pMeter = pMeasure->pDev;
	PicoSetting *pSet = (PicoSetting *)pMeasure->pSet;
	Excel *pExcel = DataMgr.GetOneWithInfo(pSet->setting.batchNo);
	if (!pExcel || !pMeter->pInstr)
	{
		LOG_ERROR("Picoammeter ThreadFunction failed null %d ", NULL == pMeter->pInstr);
		return -1;
	}
	if (pSet->setting.isSignal)
	{
		double VMax = pSet->VMax;
		double Vmin = pSet->VMin;
		double VSpan = pSet->VSpan;
		double delay = pSet->MInterval;
		double currentValue = 0;
		Stack *pVoltStack = StackAllocInit();
		double volt = 0;
		for (volt = Vmin; volt <= VMax; volt += VSpan)
		{
			pMeter->DoWithCommand(pMeter, &volt, NULL);
			DataMgr.SaveInt(pExcel, "V", volt);
			pVoltStack->InStack(pVoltStack, volt);
			if (pSet->setting.isCollector)
			{
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &currentValue, NULL);
				DataMgr.SaveDouble(pExcel, "I+", currentValue);
			}
			if (!pMeasure->isCollecting)
				return 0;
			Delay(delay);
		}

		Stack *pCurrentStack = StackAllocInit();
		while (pVoltStack->Size(pVoltStack) > 0)
		{
			volt = pVoltStack->OutStack(pVoltStack);
			pMeter->DoWithCommand(pMeter, &volt, NULL);
			if (pSet->setting.isCollector)
			{
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &currentValue, NULL);
				pCurrentStack->InStack(pCurrentStack, currentValue);
			}
			if (!pMeasure->isCollecting)
				return 0;
			Delay(delay);
		}
		while (pCurrentStack->Size(pCurrentStack) > 0)
		{
			DataMgr.SaveDouble(pExcel, "I-", pCurrentStack->OutStack(pCurrentStack));
		}

		StackDelloc(pVoltStack);
		StackDelloc(pCurrentStack);
	}

	DataMgr.Sync(pExcel);
	pMeasure->Stop(pMeasure);
	pMeter->Stop(pMeter);
	return 0;
}

static int Start(Measurement *pMea)
{

	if (!pMea)
	{
		LOG_ERROR("error in PicoammeterMeasure start");
		return -1;
	}

	pMea->isCollecting = true;
	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE, ThreadFunction, pMea, NULL);

	return 0;
}
static int Stop(Measurement *pMea)
{
	pMea->isCollecting = false;

	LOG_INFO("PicoammeterMeasure Stops");

	return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions
//==============================================================================
// Global functions
void PicoammeterMeasureInit(PicoammeterMeasure *pMea)
{
	if (NULL == pMea)
	{
		return;
	}
	MeasurementInit(&pMea->measure);
	pMea->measure.instrumentFlag = Instrument_Picoammeter;
	pMea->measure.Start = Start;
	pMea->measure.Stop = Stop;
	pMea->measure.DoMeasureWithCommand = DoMeasureWithCommand;
}
void PicoammeterMeasureDeinit(PicoammeterMeasure *pMea)
{
	MeasurementDeinit(&pMea->measure);
}
