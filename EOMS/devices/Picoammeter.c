//==============================================================================
//
// Title:		Picoammeter.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 12:01:43 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <formatio.h>
#include <utility.h>
#include <ansi_c.h>
#include "Picoammeter.h"
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
	Picoammeter *pMeter = (Picoammeter *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

		float *pVolt = (float *)inData;
    LOG_INFO("before viPrintf");
		status = viPrintf(session, ":SOUR1:VOLT %f\n", *pVolt);
	LOG_INFO("after viPrintf");	
	}
	else
	{
	    LOG_ERROR("Picoammeter DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int Start(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Picoammeter start");
		return -1;
	}
		Picoammeter *pMeter = (Picoammeter *)pDev; 
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
        LOG_INFO("Picoammeter starts");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

		status = viPrintf(session, "*RST\n");
		status = viPrintf(session, ":SOUR1:VOLT:RANG 30\n");
		status = viPrintf(session, ":SOUR1:DELay:AUTO OFF\n");
		status = viPrintf(session, ":OUTP1 ON\n");
		
	}
	else
	{
		LOG_ERROR("Picoammeter Start failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int SetAttribute(struct Device *pDev)
{
	Picoammeter *pMeter = (Picoammeter *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("Picoammeter SetAttribute");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

		status = viSetAttribute(session, VI_ATTR_TMO_VALUE, 10000);
		status = viSetAttribute(session, VI_ATTR_ASRL_BAUD, 9600);
		status = viSetAttribute(session, VI_ATTR_ASRL_DATA_BITS, 8);
		status = viSetAttribute(session, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);
		status = viSetAttribute(session, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);
		status = viSetAttribute(session, VI_ATTR_TERMCHAR_EN, VI_TRUE);
		status = viSetAttribute(session, VI_ATTR_TERMCHAR, 0x0D);

		pMeter->device.pInstr->QueryID(pMeter->device.pInstr);
	}
	else
	{
		LOG_ERROR("Picoammeter SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
	}
	return 0;
}
static int Stop(Device *pDev)
{

	Picoammeter *pMeter = (Picoammeter *)pDev;
	LOG_INFO("Picoammeter Stops");
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;
		status = viPrintf(session, ":OUTP1 OFF\n");
		status = viPrintf(session, "*RST\n");
	}
	else
	{
		LOG_ERROR("Picoammeter Stop failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
void PicoammeterInit(Picoammeter *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	DeviceInit(&pDev->device);
	memcpy(pDev->device.name, "Picoammeter", sizeof("Picoammeter"));
	pDev->SetAttribute = SetAttribute;
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
}
void PicoammeterDeinit(Picoammeter *pDev)
{
	memcpy(pDev->device.name, "Picoammeter", sizeof("Picoammeter"));
	DeviceDeinit(&pDev->device);
}
