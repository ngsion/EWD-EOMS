//==============================================================================
//
// Title:		WaveformGenerator.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-09-15 at 17:36:30 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <formatio.h>
#include <utility.h>
#include <ansi_c.h>
#include "WaveformGenerator.h"
#include "log.h"
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
	WaveformGenerator *pMeter = (WaveformGenerator *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		
	}
	else
	{
		log_error("WaveformGenerator DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int Start(Device *pDev)
{
	if (!pDev)
	{
		log_error("error in WaveformGenerator start");
		return -1;
	}
		WaveformGenerator *pMeter = (WaveformGenerator *)pDev; 
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
        log_info("WaveformGenerator starts");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

	}
	else
	{
		log_error("WaveformGenerator Start failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int Stop(Device *pDev)
{

	WaveformGenerator *pMeter = (WaveformGenerator *)pDev;
	log_info("WaveformGenerator Stops");
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

	}
	else
	{
		log_error("WaveformGenerator Stop failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
void WaveformGeneratorInit(WaveformGenerator *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	DeviceInit(&pDev->device);
	memcpy(pDev->device.name, "WaveformGenerator", sizeof("WaveformGenerator"));
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
}
void WaveformGeneratorDeinit(WaveformGenerator *pDev)
{
	memcpy(pDev->device.name, "WaveformGenerator", sizeof("WaveformGenerator"));
	DeviceDeinit(&pDev->device);
}

