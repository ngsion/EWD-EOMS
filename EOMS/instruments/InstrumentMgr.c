//==============================================================================
//
// Title:		InstrumentMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 15:07:11 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <string.h>
#include "InstrumentMgr.h"
#include "visa.h"
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static ViSession defaultRM = 0;
static InstrumentListNode *defaultInstrList = NULL;

//==============================================================================
// Static functions
static int sFindResource()
{
	ViStatus status;
	/*
	 * First we must call viOpenDefaultRM to get the manager
	 * handle.  We will store this handle in defaultRM.
	 */
	status = viOpenDefaultRM(&defaultRM);
	if (status < VI_SUCCESS)
	{
		LOG_FATAL("Could not open a session to the VISA Resource Manager!");
		return -1;
	}

	ViUInt32 numInstrs;
	ViFindList findList;
	char instrResourceString[VI_FIND_BUFLEN];

	/* Find all the  resources in our system and store the  */
	/* number of resources in the system in numInstrs.                  */
	status = viFindRsrc(defaultRM, "?*INSTR", &findList, &numInstrs, instrResourceString);

	if (status < VI_SUCCESS)
	{
		LOG_FATAL("An error occurred while finding resources.");
		viClose(defaultRM);
		return -1;
	}
	LOG_INFO(" %d instruments are detected. defaultRM is %d", numInstrs, defaultRM);

	unsigned short intfType;
	unsigned short intfNum;
	int i = numInstrs;
	while (i > 0)
	{

		status = viParseRsrc(defaultRM, instrResourceString, &intfType, &intfNum);

		LOG_INFO("instrument %s is connected, intfType is %d,intfNum is %d.", instrResourceString, intfType, intfNum);

		if (intfType != VI_INTF_ASRL && intfType != VI_INTF_USB && intfType != VI_INTF_GPIB)
		{
			--i;
			continue;
		}

		Instrument *pInstr = InstrumentAllocInit();
		pInstr->resouceMgr = defaultRM;
		pInstr->type = intfType;
		pInstr->status = Instrument_Status_Connected;
		memcpy(pInstr->address, instrResourceString, VI_FIND_BUFLEN);

		InstrumentListPushBack(InstrMgr.plist, pInstr);

		if (i > 1)
		{
			status = viFindNext(findList, instrResourceString);
			if (status < VI_SUCCESS)
			{
				LOG_ERROR("Error viFindNext %d.", status);
				break;
			}
		}

		--i;
	}

	return 0;
}

static int Init(int x)
{
	return sFindResource(x);
}
static int Open(InstrumentMgr *pMgr)
{
	InstrumentListNode *cur = *(pMgr->plist);
	InstrumentListNode *next = NULL;
	while (NULL != cur)
	{
		next = cur->next;
		if(-1 == cur->pInstr->Open(cur->pInstr))
		{
			LOG_ERROR("Error open %s. delete it", cur->pInstr->address);
			InstrumentListDeleteOne(pMgr->plist,cur->pInstr);
		}
		cur = next;
	}

	return 0;
}

static int QueryID(InstrumentMgr *pMgr)
{
	InstrumentListNode *cur = *(pMgr->plist);
	InstrumentListNode *next = NULL;
	while (NULL != cur)
	{
		next = cur->next;
		cur->pInstr->QueryID(cur->pInstr);
		cur = next;
	}

	return 0;
}

static int Shutdown(int x)
{
	if (NULL != defaultRM)
	{
		//	viClose(defaultRM);
	}
	InstrumentListClear(&defaultInstrList);
	return 0;
}

//==============================================================================
// Global variables

InstrumentMgr InstrMgr = {
	.plist = &defaultInstrList,
	.Open = Open,
	.QueryID = QueryID,
	.Init = Init,
	.Shutdown = Shutdown

};

//==============================================================================
// Global variables

//==============================================================================
// Global functions
