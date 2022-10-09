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

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static FILE *fp = NULL;

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

	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		LOG_INFO("Init one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Open(pNode->pInstr);
		Device *pMeter = NULL;
		Measurement *pMeasure = NULL;
		if (Instrument_Type_ASRL == pNode->pInstr->type)
		{
			pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
			if (NULL != pMeter)
			{
				SetMgr.online |= Online_Picoammieter;
				pMeter->pInstr = pNode->pInstr;
			}

			pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_Picoammeter);
			if (NULL != pMeasure)
			{
				pMeasure->pInstr = pNode->pInstr;
			}
		}
		else if (Instrument_Type_USB == pNode->pInstr->type)
		{

			pMeter = DevMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
			if (NULL != pMeter)
			{
				SetMgr.online |= Online_WaveformGenerator;
				pMeter->pInstr = pNode->pInstr;
			}

			pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
			if (NULL != pMeasure)
			{
				pMeasure->pInstr = pNode->pInstr;
			}
		}
		else if (Instrument_Type_GPIB == pNode->pInstr->type)
		{
			pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
			if (NULL != pMeter)
			{
				SetMgr.online |= Online_LCRMeter;
				pMeter->pInstr = pNode->pInstr;
			}

			pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_LCRMeter);
			if (NULL != pMeasure)
			{
				pMeasure->pInstr = pNode->pInstr;
			}
		}
		pHead = pNode->next;
	}

	DevMgr.AfterInit(0);
	return 0;
}
static int Shutdown(int x)
{
	if (NULL != fp)
	{
		// fclose(fp);
	}
	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		LOG_INFO("Shutdown one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Close(pNode->pInstr);
		pHead = pNode->next;
	}
	InstrMgr.Shutdown(x);
	DevMgr.Shutdown(x);
	MeasureMgr.Shutdown(x);
	SetMgr.Shutdown(x);
	return 0;
}

static int Stop(int x)
{
	System.isWorking = false;
	MeasureMgr.Stop(x);
	DevMgr.Stop(x);
	DataMgr.Stop(x);
	return 0;
}

static int LoadSettings(int x)
{
	int i;
	for (i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != DevMgr.pDevArray[i])
		{
			bool flag = false;
			if ((SetMgr.signal & Signal_Picoammieter) && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_Picoammeter))
			{
				flag = true;
			}
			else if ((SetMgr.signal & Signal_WaveformGenerator) && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_WaveformGenerator))
			{
				flag = true;
			}
			else if ((SetMgr.signal & Signal_LCRMeter) && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_LCRMeter))
			{
				flag = true;
			}
			DevMgr.pDevArray[i]->isSignal = flag;
		}
	}

	for (i = 0; i < MEASURE_MAX_NUM; i++)
	{
		if (NULL != MeasureMgr.pMeasureArray[i])
		{
			bool flag = false;
			if ((SetMgr.data & Data_Cp) && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_LCRMeter))
			{
				flag = true;
			}
			else if ((SetMgr.data & Data_D) && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_LCRMeter))
			{
				flag = true;
			}
			else if ((SetMgr.data & Data_Current) && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_Picoammeter))
			{
				flag = true;
			}
			MeasureMgr.pMeasureArray[i]->isCollector = flag;
		}
	}


	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
	if (Signal_Picoammieter == SetMgr.signal)
	{
		Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_Picoammeter);

		if (NULL != pMeter && NULL != pMeasure)
		{
			int index = 0;
			float volt = 0;
			double value = 0;
			for (index = 0; index <= 15; index++)
			{
				float volt = index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				DataMgr.SaveInt("V", volt);
				pMeasure->DoMeasureWithCommand(pMeasure, NULL, &value);
				DataMgr.SaveDouble("I+", value);
				Delay(1);
			}

			Stack *pStack = StackAllocInit();
			for (index = 0; index <= 15; index++)
			{
				float volt = 30 - index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				pMeasure->DoMeasureWithCommand(pMeasure, NULL, &value);
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
	else if (Signal_LCRMeter == SetMgr.signal)
	{
		Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_LCRMeter);
		if (NULL != pMeter && NULL != pMeasure)
		{
			int index = 0;
			double value = 0;
			double dvalue = 0.0;
			float volt = 0;
			for (index = 0; index <= 15; index++)
			{
				volt = index * 2;
				pMeter->DoWithCommand(pMeter, &volt, NULL);
				DataMgr.SaveInt("V", volt);
				pMeasure->DoMeasureWithCommand(pMeasure, &dvalue, &value);
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
				pMeasure->DoMeasureWithCommand(pMeasure, &dvalue, &value);
				cStack->InStack(cStack,value);
				dStack->InStack(dStack,dvalue);
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
	else
	{

		MeasureMgr.Start(0);
	}
	return 0;
}

static int Start(int x)
{
	System.isWorking = true;
	DevMgr.Start(x);
	DataMgr.Start(x);

	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE, ThreadFunction, NULL, NULL);

	return 0;
}
//==============================================================================
// Global variables
EOMSystem System = {
	.isWorking = false,
	.Init = Init,
	.Shutdown = Shutdown,
	.LoadSettings = LoadSettings,
	.Start = Start,
	.Stop = Stop};

//==============================================================================
// Global functions
