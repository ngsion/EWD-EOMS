//==============================================================================
//
// Title:		Device.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 12:12:47 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <visa.h>
#include "Device.h"
#include <string.h>
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int Reset(struct Device *pDev)
{
	LOG_INFO("Device Reset");

	if (NULL != pDev->pInstr && pDev->pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pDev->pInstr->session;
        status = viPrintf(session, "*RST\n");
	}
	else
	{
		LOG_ERROR("Device Reset failed null %d ", NULL == pDev->pInstr);
	}

	return 0;
}
static int Start(Device *pDev)
{
	LOG_INFO("Device starts");
	return 0;
}
static int Stop(Device *pDev)
{
	LOG_INFO("Device Stops");
	return 0;
}
static int QueryID(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Device QueryID");
		return -1;
	}
	
	if (NULL != pDev->pInstr)
	{
         pDev->pInstr->QueryID(pDev->pInstr);
	}
	return 0;
}
static int DoWithCommand(struct Device *pDev, void *inData, void *outData)
{
	LOG_INFO("Device DoWithCommand");
	return 0;
}


//==============================================================================
// Global variables

//==============================================================================
// Global functions

void DeviceInit(Device *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	pDev->instrumentFlag = 0;
	pDev->pInstr = NULL;
	pDev->isSignal = false;
	pDev->Start = Start;
	pDev->Stop = Stop;
	pDev->QueryID = QueryID;
	pDev->DoWithCommand = DoWithCommand;
	pDev->Reset = Reset;
}
void DeviceDeinit(Device *pDev)
{
	pDev->instrumentFlag = 0;
	pDev->pInstr = NULL;
}
