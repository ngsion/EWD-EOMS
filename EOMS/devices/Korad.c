//==============================================================================
//
// Title:		Korad.c
// Purpose:		A short description of the implementation.
//
// Created on:	2024-05-05 at 21:11:21 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Korad.h"
#include <formatio.h>
#include <utility.h>
#include <ansi_c.h>
#include "logger.h"
#include "visa.h"
#include <string.h>
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int DoWithCommand(struct Device *pDev, void *inData, void *outData)
{
	Korad *pMeter = (Korad *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

	
	}
	else
	{
		LOG_ERROR("Korad DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int SetAttribute(struct Device *pDev)
{
	Korad *pMeter = (Korad *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("Korad SetAttribute");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

 		status = viSetAttribute(session, VI_ATTR_ASRL_BAUD, 9600);
		status = viSetAttribute(session, VI_ATTR_ASRL_DATA_BITS, 8);
		status = viSetAttribute(session, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);
		status = viSetAttribute(session, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);
	//	status = viSetAttribute(session, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	//	status = viSetAttribute(session, VI_ATTR_TERMCHAR, 0x0D);
	}
	else
	{
		LOG_ERROR("Korad SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
	}
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
		return SetAttribute(pDev);
	}

	LOG_ERROR("Error Connect %s", pDev->pInstr->address);
	return -1;
}

static int Start(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Korad start");
		return -1;
	}
	ViStatus status = VI_SUCCESS;
	Korad *pMeter = (Korad *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("Korad starts");

		ViSession session = pMeter->device.pInstr->session;
	 
	}
	else
	{
		LOG_ERROR("Korad Start failed null %d ", NULL == pMeter->device.pInstr);
	}
	if (status < VI_SUCCESS)
	{
		LOG_ERROR("status is %d.", status);
	}
	return 0;
}

static int Stop(Device *pDev)
{

	Korad *pMeter = (Korad *)pDev;
	LOG_INFO("Korad Stops");
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;
		status = viPrintf(session, ":OUTP1 OFF\n");
	}
	else
	{
		LOG_ERROR("Korad Stop failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
void KoradInit(Korad *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	DeviceInit(&pDev->device);
	pDev->device.instrumentFlag = Instrument_Picoammeter;
	pDev->device.Connect = Connect;
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
	pDev->device.type = Instrument_Type_ASRL;
}
void KoradDeinit(Korad *pDev)
{
	pDev->device.instrumentFlag = Instrument_Picoammeter;
	DeviceDeinit(&pDev->device);
}
