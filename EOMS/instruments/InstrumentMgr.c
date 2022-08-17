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
#include "../logger/log.h"

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
		log_fatal("Could not open a session to the VISA Resource Manager!\n");
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
		log_fatal("An error occurred while finding resources.\n");
		viClose(defaultRM);
		return -1;
	}
	log_info(" %d instruments are detected.\n", numInstrs);

	unsigned short intfType;
	unsigned short intfNum;
	int i = numInstrs;
	while (i > 0)
	{

		status = viParseRsrc(defaultRM, instrResourceString, &intfType, &intfNum);

		log_info("instrument %s is connected, intfType is %d,intfNum is %d.\n", instrResourceString, intfType, intfNum);

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
				log_error("Error viFindNext %d.\n", status);
				break;
			}
		}

		--i;
	}

	return 0;
}

static int sInit(int x)
{
	sFindResource(x);
	return 0;
}
static int sShutdown(int x)
{
	if (NULL != defaultRM)
	{
		viClose(defaultRM);
	}
	return 0;
}

//==============================================================================
// Global variables

InstrumentMgr InstrMgr = {
	.plist = &defaultInstrList,
	.Init = sInit,
	.Shutdown = sShutdown

};

//==============================================================================
// Global variables

//==============================================================================
// Global functions
