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
static int Reset(struct Device *pDev)
{
	LOG_INFO("LCRMeter Reset");

	if (NULL != pDev->pInstr && pDev->pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pDev->pInstr->session;
        status = viPrintf(session, "*RST\n");
		status = viPrintf(session, "FUNC:IMP CPD\n");
		//status = viPrintf(session, "FREQ MIN\n"); ///MIN=20Hz, MAX=1MHz
		status = viPrintf(session, "VOLT 0mV\n");
		//status = viPrintf(session, "APER FAST\n");
	}
	else
	{
		LOG_ERROR("LCRMeter Reset failed null %d ", NULL == pDev->pInstr);
	}

	return 0;
}
static int DoWithCommand(struct Device *pDev, void *inData, void *outData)
{
	LCRMeter *pMeter = (LCRMeter *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
        double *pVolt = (double *)inData;
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;
		status = viPrintf(session, "BIAS:VOLT %0.2f\n",*pVolt);
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
	ViStatus status = VI_SUCCESS;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("LCRMeter starts");

		ViSession session = pMeter->device.pInstr->session;
		status = viPrintf(session, "FUNC:IMP CPD\n");
		status = viPrintf(session, "FREQ 1kHz\n");
		status = viPrintf(session, "VOLT 0.5V\n");
		status = viPrintf(session, "APERture MED\n");
		status = viPrintf(session, "BIAS:VOLT 0\n");
		status = viPrintf(session, "BIAS:STATE 1\n");

	}
	else
	{
		LOG_ERROR("LCRMeter Start failed null %d ", NULL == pMeter->device.pInstr);
	}
	if (status < VI_SUCCESS)
	{
		LOG_ERROR("status is %d.", status);
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
		status = viPrintf(session, "BIAS:STATE 0\n");
		
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
	pDev->device.instrumentFlag = Instrument_LCRMeter; 
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
	pDev->device.Reset = Reset;
	pDev->device.type = Instrument_Type_GPIB;
}
void LCRMeterDeinit(LCRMeter *pDev)
{
	pDev->device.instrumentFlag = Instrument_LCRMeter; 
	DeviceDeinit(&pDev->device);
}
