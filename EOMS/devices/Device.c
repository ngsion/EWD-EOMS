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
	if (!pDev)
	{
		LOG_ERROR("error in Device Reset");
		return -1;
	}

	if (NULL != pDev->pInstr)
	{
		if (pDev->pInstr->status >= Instrument_Status_Open)
		{
			ViStatus status;
			ViSession session = pDev->pInstr->session;
			status = viPrintf(session, "*RST\n");

			if (status < VI_SUCCESS)
			{
				LOG_ERROR("Device Reset %d.", status);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			LOG_ERROR("Device Reset failed status %d ", pDev->pInstr->status);
		}
	}
	else
	{
		LOG_ERROR("Device Reset failed null %d ", NULL == pDev->pInstr);
	}
	return -1;
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
static int Connect(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Device Connect");
		return -1;
	}

	if (0 == pDev->pInstr->Open(pDev->pInstr))
	{
		return 0;
	}

	LOG_ERROR("Error Connect %s", pDev->pInstr->address);
	return -1;
}
static int QueryID(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Device QueryID");
		return -1;
	}

	if (0 == pDev->pInstr->QueryID(pDev->pInstr))
	{
		LOG_INFO("QueryID one instrument is %s, id %s", pDev->pInstr->address, pDev->pInstr->identifier);
		return 0;
	}

	LOG_ERROR("Error QueryID %s", pDev->pInstr->address);
	return -1;
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
	pDev->pSet = NULL;
	pDev->Start = Start;
	pDev->Stop = Stop;
	pDev->QueryID = QueryID;
	pDev->Connect = Connect;
	pDev->DoWithCommand = DoWithCommand;
	pDev->Reset = Reset;
	pDev->type = Instrument_Type_UNKNOWN;
}
void DeviceDeinit(Device *pDev)
{
	pDev->instrumentFlag = 0;
	pDev->pInstr = NULL;
	pDev->pSet = NULL;
}
