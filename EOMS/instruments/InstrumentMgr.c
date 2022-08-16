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

#include "InstrumentMgr.h"
#include "visa.h"
#include "../logger/log.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static ViSession defaultRM = NULL;

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

	int i = numInstrs;
	while (i >= 0)
	{
		log_info("instrResourceString is %s.\n", instrResourceString);
		if (VI_SUCCESS != viFindNext(findList, instrResourceString))
			break;
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
	.Init = sInit,
	.Shutdown = sShutdown

};

//==============================================================================
// Global variables

//==============================================================================
// Global functions
