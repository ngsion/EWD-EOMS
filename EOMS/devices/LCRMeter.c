//==============================================================================
//
// Title:		LCRMeter.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-09-24 at 21:12:44 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LCRMeter.h"
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
// Static functions
static int DoWithCommand(struct Device *pDev, void *inData, void *outData)
{
	LCRMeter *pMeter = (LCRMeter *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;


	}
	else
	{
	    LOG_ERROR("LCRMeter DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int Start(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in LCRMeter start");
		return -1;
	}
		LCRMeter *pMeter = (LCRMeter *)pDev; 
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
        LOG_INFO("LCRMeter starts");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;


		
	}
	else
	{
		LOG_ERROR("LCRMeter Start failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int SetAttribute(struct Device *pDev)
{
	LCRMeter *pMeter = (LCRMeter *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("LCRMeter SetAttribute");
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
		LOG_ERROR("LCRMeter SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
	}
	return 0;
}
static int Stop(Device *pDev)
{

	LCRMeter *pMeter = (LCRMeter *)pDev;
	LOG_INFO("LCRMeter Stops");
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

	}
	else
	{
		LOG_ERROR("LCRMeter Stop failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
void LCRMeterInit(LCRMeter *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	DeviceInit(&pDev->device);
	memcpy(pDev->device.name, DEVICE_LCRMETER_STR, sizeof(DEVICE_LCRMETER_STR));
	pDev->SetAttribute = SetAttribute;
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
}
void LCRMeterDeinit(LCRMeter *pDev)
{
	memcpy(pDev->device.name, DEVICE_LCRMETER_STR, sizeof(DEVICE_LCRMETER_STR));
	DeviceDeinit(&pDev->device);
}
