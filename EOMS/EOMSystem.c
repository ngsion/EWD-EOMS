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

	InstrumentListNode *pHead = *InstrMgr.plist;
	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		log_info("Init one instrument is %s", pNode->pInstr->address);
		pNode->pInstr->Open(pNode->pInstr);
		if( Instrument_Type_ASRL ==  pNode->pInstr->type){
			
		    ((Device*) (DevMgr.pDevArray[0]))->pInstr = pNode->pInstr;
			MeasureMgr.pMeasure->pInstr = pNode->pInstr; 
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

static int Start(int x)
{
	DevMgr.Start(x);
    MeasureMgr.Start(x);
	return 0;
}
static int Stop(int x)
{
	DevMgr.Stop(x);
	MeasureMgr.Stop(x);
	return 0;
}

//==============================================================================
// Global variables
EOMSystem System = {
	.Init = Init,
	.Shutdown = Shutdown,
	.Start = Start,
	.Stop = Stop
	};

//==============================================================================
// Global functions
