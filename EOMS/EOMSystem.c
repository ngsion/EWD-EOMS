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

#include <utility.h>
#include "EOMSystem.h"
#include "logger.h"
#include <time.h>
#include <assert.h>
#include <string.h>
#include "SettingMgr.h"

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
		int i = 0;
		if (Instrument_Type_ASRL == pNode->pInstr->type)
		{
			for (i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_Picoammeter))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for (i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_Picoammeter))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
		}
		else if (Instrument_Type_USB == pNode->pInstr->type)
		{

			for (i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_WaveformGenerator))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for (i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_WaveformGenerator))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
		}
		else if (Instrument_Type_GPIB == pNode->pInstr->type)
		{
			for (i = 0; i < DEVICE_MAX_NUM; i++)
			{
				if (NULL != DevMgr.pDevArray[i] && (DevMgr.pDevArray[i]->instrumentFlag == Instrument_LCRMeter))
				{
					DevMgr.pDevArray[i]->pInstr = pNode->pInstr;
					break;
				}
			}
			for (i = 0; i < MEASURE_MAX_NUM; i++)
			{
				if (NULL != MeasureMgr.pMeasureArray[i] && (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_LCRMeter))
				{
					MeasureMgr.pMeasureArray[i]->pInstr = pNode->pInstr;
					break;
				}
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

static int Start(int x)
{
	System.isWorking = true;
	DevMgr.Start(x);
	MeasureMgr.Start(x);

	return 0;
}
static int Stop(int x)
{
	System.isWorking = false;
	MeasureMgr.Stop(x);
	DevMgr.Stop(x);

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
