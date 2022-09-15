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
#include "DeviceMgr.h"
#include "MeasurementMgr.h"

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

	fp = fopen(buf, "a+");
	if (NULL != fp)
	{
		int result = log_add_fp(fp, LOG_DEBUG);
		if (result < 0)
		{
			log_fatal("log_add_fp failed");
		}
	}
	else
	{
		perror("error fopen");
	}
	// log_set_quiet(true);
}

//==============================================================================
// Static functions
static int Init(int x)
{
	setupLogger();
	InstrMgr.Init(x);
	DevMgr.Init(x);
	MeasureMgr.Init(x);

	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		log_info("Init one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Open(pNode->pInstr);
		if (Instrument_Type_ASRL == pNode->pInstr->type)
		{

			((Device *)(DevMgr.pDevArray[0]))->pInstr = pNode->pInstr;
			MeasureMgr.pPicoammeterMeasure->pInstr = pNode->pInstr;
		}
		pHead = pNode->next;
	}

	DevMgr.AfterInit(x);
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
		log_info("Shutdown one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Close(pNode->pInstr);
		pHead = pNode->next;
	}
	InstrMgr.Shutdown(x);
	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
	Device *pDev = ((Device *)(DevMgr.pDevArray[0]));
	Measurement *pMeasure = MeasureMgr.pPicoammeterMeasure;
	int max = 30;
	int min = 0;
	int step = 2;
	double current = 0.0;
	int volt;
	
	for ( volt = min; volt <= max; volt += step)
	{

		pDev->DoWithCommand(pDev,&volt, NULL);
		Delay(0.01);
		pMeasure->DoCollectWithCommand(pMeasure,&volt, &current);

	    log_info("instrument  %d set volt %dV get current %fnA ", pDev->pInstr->session, volt, current);
		Delay(1);
	}

    

	return 0;
}

static int CVICALLBACK ThreadFunction2(void *functionData)
{
Device *pDev = ((Device *)(DevMgr.pDevArray[0]));
	Measurement *pMeasure = MeasureMgr.pPicoammeterMeasure;
	int max = 30;
	int min = 0;
	int step = 2;
	double current = 0.0;
	int volt;
	
	for ( volt = min; volt <= max; volt += step)
	{

	    log_info("instrument  %d  get current %fnA ", pDev->pInstr->session, current);
		Delay(1);
	}

    

	return 0;
}

static int Start(int x)
{
	DevMgr.Start(x);
	MeasureMgr.Start(x);

	int threadFunctionId = 0;
	
	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,
								  ThreadFunction2, NULL,
								  &threadFunctionId);
		/* Wait for the thread functions to finish executing */
	CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,
											threadFunctionId,
											0);
	
	/* Release thread functions */
	CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadFunctionId);

	return 0;
}
static int Stop(int x)
{
	MeasureMgr.Stop(x);
	DevMgr.Stop(x);

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
