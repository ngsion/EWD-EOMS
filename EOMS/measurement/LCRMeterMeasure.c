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
#include "DataSaveMgr.h"
#include "LCRMeterMeasure.h"
#include <visa.h>
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include "logger.h"
#include <string.h>
#include "LCRSetting.h"
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

static int CVICALLBACK ThreadFunction(void *functionData)
{

	Measurement *pMeasure = (Measurement *)functionData;
	Device *pMeter = pMeasure->pDev;
	LCRSetting *pSet = (LCRSetting *)pMeasure->pSet;
	Excel *pExcel = DataMgr.GetOneWithInfo("lcr",pSet->setting.batchNo);
	if (!pExcel || !pMeter->pInstr)
	{
		LOG_ERROR("LCRammeter ThreadFunction failed null %d ", NULL == pMeter->pInstr);
		return -1;
	}

	if (pSet->setting.isSignal)
	{
		double VMax = pSet->VMax;
		double Vmin = pSet->VMin;
		double VSpan = pSet->VSpan;
		double delay = pSet->MInterval;

		double value = 0;
		double dvalue = 0.0;
		Stack *pVoltStack = StackAllocInit();
		double volt = 0;
		for (volt = Vmin; volt <= VMax; volt += VSpan)
		{

			pMeter->DoWithCommand(pMeter, &volt, NULL);
			DataMgr.SaveInt(pExcel, "V", volt);
			pVoltStack->InStack(pVoltStack, volt);
			if (pSet->setting.isCollector)
			{
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, &dvalue);
				DataMgr.SaveDouble(pExcel,"C(+)", value);
				DataMgr.SaveKey(pExcel,"C(-)");
				DataMgr.SaveDouble(pExcel,"D(+)", dvalue);
			}
			if (!pMeasure->isCollecting)
				return 0;
			Delay(delay);
		}

		Stack *cStack = StackAllocInit();
		Stack *dStack = StackAllocInit();
		while (pVoltStack->Size(pVoltStack) > 0)
		{
			volt = pVoltStack->OutStack(pVoltStack);
			pMeter->DoWithCommand(pMeter, &volt, NULL);
			if (pSet->setting.isCollector)
			{
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, &dvalue);
				cStack->InStack(cStack, value);
				dStack->InStack(dStack, dvalue);
			}
			if (!pMeasure->isCollecting)
				return 0;
			Delay(delay);
		}
		while (cStack->Size(cStack) > 0)
		{
			DataMgr.SaveDouble(pExcel, "C(-)", cStack->OutStack(cStack));
		}
		while (dStack->Size(dStack) > 0)
		{
			DataMgr.SaveDouble(pExcel, "D(-)", dStack->OutStack(dStack));
		}

		StackDelloc(pVoltStack);
		StackDelloc(cStack);
		StackDelloc(dStack);

		LOG_INFO("LCRMeter ThreadFunction end");
	}
	DataMgr.Stop(0);
	pMeasure->Stop(pMeasure);
	pMeter->Stop(pMeter);
	return 0;
}
static int Start(Measurement *pMea)
{

	if (!pMea)
	{
		LOG_ERROR("error in LCRMeterMeasure start");
		return -1;
	}

	pMea->isCollecting = true;
	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE, ThreadFunction, pMea, NULL);

	return 0;
}
static int Stop(Measurement *pMea)
{
	pMea->isCollecting = false;

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
