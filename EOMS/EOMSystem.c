//==============================================================================
//
// Title:		EOMSystem.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 11:22:05 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "DataSaveMgr.h"
#include <utility.h>
#include "EOMSystem.h"
#include "logger.h"
#include <time.h>
#include <assert.h>
#include <string.h>
#include "SettingMgr.h"
#include "Stack.h"
#include "PicoSetting.h"
#include "Excel.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

void setupLogger()
{
	time_t now; // time_t
	time(&now);

	struct tm *tblock;
	tblock = localtime(&now);

	char buf[64] = {0};
	strftime(buf, 64, "log/EOMSlog_%Y%m%d_%H%M%S.txt", tblock);

	//	logger_initConsoleLogger(NULL);
	logger_initFileLogger(buf, 0, 0);
	logger_setLevel(LogLevel_DEBUG);
	logger_autoFlush(5000);
}

//==============================================================================
// Static functions
static int Init(int x)
{
	 
	setupLogger();
	InstrMgr.Init(x);
	DevMgr.Init(x);
	MeasureMgr.Init(x);
	SetMgr.Init(x);

	for (int index = Instrument_Picoammeter; index < Instrument_Korad; index++)
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(index);
		Device *pDevice = DevMgr.FindWithInstrFlag(index);
		Measurement *pMea = MeasureMgr.FindWithInstrFlag(index);
		pDevice->pSet = pSet;
		if (pMea)
		{
		  pMea->pSet = pSet;
          pMea->pDev = pDevice;
		}
	}
	return 0;
}
static int Shutdown(int x)
{
	DevMgr.Shutdown(x);
	MeasureMgr.Shutdown(x);
	InstrMgr.Shutdown(x);
	SetMgr.Shutdown(x);
	DataMgr.Stop(x); 
	logger_flush();
	return 0;
}

static int Stop(int x)
{

	MeasureMgr.Stop(x);
	DevMgr.Reset(x);
	DevMgr.Stop(x);
	DataMgr.Stop(x);

	return 0;
}

/*
static int CVICALLBACK ThreadFunction(void *functionData)
{
	Delay(1);
	//	if (Signal_Picoammieter == SetMgr.signal)
	{
		DevMgr.Start(0);

		Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_Picoammeter);

		if (NULL != pMeter && NULL != pMeasure)
		{
			int index = 0;
			double volt = 0;
			double value = 0;
			for (index = 0; index <= 15; index++)
			{
				double volt = index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				DataMgr.SaveInt("V", volt);
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, NULL);
				DataMgr.SaveDouble("I+", value);
				Delay(1);
			}

			Stack *pStack = StackAllocInit();
			for (index = 0; index <= 15; index++)
			{
				double volt = 30 - index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, NULL);
				pStack->InStack(pStack, value);
				Delay(1);
			}
			while (pStack->Size(pStack) > 0)
			{
				DataMgr.SaveDouble("I-", pStack->OutStack(pStack));
			}
			StackDelloc(pStack);

			LOG_INFO("Picoammeter ThreadFunction end");
		}
		Stop(0);
		return 0;
	}
	//	else if (Signal_LCRMeter == SetMgr.signal)
	{

		DevMgr.Start(0);

		Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_LCRMeter);
		if (NULL != pMeter && NULL != pMeasure)
		{
			int index = 0;
			double value = 0;
			double dvalue = 0.0;
			double volt = 0;
			for (index = 0; index <= 15; index++)
			{
				volt = index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				DataMgr.SaveInt("V", volt);
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, &dvalue);
				DataMgr.SaveDouble("C(+)", value);
				DataMgr.SaveKey("C(-)");
				DataMgr.SaveDouble("D(+)", dvalue);
				Delay(0.5);
			}

			Stack *cStack = StackAllocInit();
			Stack *dStack = StackAllocInit();
			for (index = 0; index <= 15; index++)
			{
				volt = 30 - index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				pMeasure->DoMeasureWithCommand(pMeasure, &volt, &value, &dvalue);
				cStack->InStack(cStack, value);
				dStack->InStack(dStack, dvalue);
				Delay(0.5);
			}
			while (cStack->Size(cStack) > 0)
			{
				DataMgr.SaveDouble("C(-)", cStack->OutStack(cStack));
			}
			while (dStack->Size(dStack) > 0)
			{
				DataMgr.SaveDouble("D(-)", dStack->OutStack(dStack));
			}
			StackDelloc(cStack);
			StackDelloc(dStack);

			LOG_INFO("LCRMeter ThreadFunction end");
		}
		Stop(0);
		return 0;
	}
	//	else
	{

		MeasureMgr.Start(0);

		Delay(1);
		DevMgr.Start(0);
	}
	return 0;
}
*/
static int Start(int x)
{
	DataMgr.Start(0);
    DevMgr.Reset(x);
	DevMgr.Start(x);
	
    MeasureMgr.Start(0);

	return 0;
}
//==============================================================================
// Global variables
EOMSystem System = {
	.Init = Init,
	.Shutdown = Shutdown,
	.Start = Start,
	.Stop = Stop};

//==============================================================================
// Global functions
