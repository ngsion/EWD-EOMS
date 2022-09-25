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
	WaveformGenerator *pMeter = (WaveformGenerator *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		
	}
	else
	{
		LOG_ERROR("WaveformGenerator DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int Start(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in WaveformGenerator start");
		return -1;
	}
	ViStatus status = VI_SUCCESS; 
		WaveformGenerator *pMeter = (WaveformGenerator *)pDev; 
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
        LOG_INFO("WaveformGenerator starts");
		ViSession session = pMeter->device.pInstr->session;

		  	viPrintf(session,"*CLS\n");
			viPrintf(session,"SOURce1:FUNCtion SQU\n");
			viPrintf(session,"SOURce1:FREQuency +5\n");
			viPrintf(session,"SOURce1:VOLTage:HIGH +6.0\n");
			viPrintf(session,"SOURce1:VOLTage:LOW 0.0\n"); 
			viPrintf(session,"SOURce1:VOLTage:OFFSet 0\n");
		//viPrintf(session,"SOURce1:VOLTage:PHASe 90\n");
			viPrintf(session, "OUTPut1 ON\n");  /* Turn on the instrument output */
         //	viPrintf(instr, "SOURce1:*TRG\n");  /* Send bus trigger */
		 
		    viPrintf(session,"SOURce2:FUNCtion DC\n"); 
		 	//viPrintf(session,"SOURce2:FREQuency +5\n");
		 	viPrintf(session,"SOURce2:VOLTage:OFFSet -3.0\n");
			viPrintf(session, "OUTPut2 ON\n");
	}
	else
	{
		LOG_ERROR("WaveformGenerator Start failed null %d ", NULL == pMeter->device.pInstr);
	}
if (status < VI_SUCCESS)
	{
		LOG_ERROR("status is %d.", status);
	}
	return 0;
}

static int Stop(Device *pDev)
{

	WaveformGenerator *pMeter = (WaveformGenerator *)pDev;
	LOG_INFO("WaveformGenerator Stops");
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;
        viPrintf(session, "OUTPut2 OFF\n");
		viPrintf(session, "OUTPut1 OFF\n");
	}
	else
	{
		LOG_ERROR("WaveformGenerator Stop failed null %d ", NULL == pMeter->device.pInstr);
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
	memcpy(pDev->device.name, DEVICE_WAVEFORMGENTERATOR_STR, sizeof(DEVICE_WAVEFORMGENTERATOR_STR));
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;
}
void WaveformGeneratorDeinit(WaveformGenerator *pDev)
{
	memcpy(pDev->device.name, DEVICE_WAVEFORMGENTERATOR_STR, sizeof(DEVICE_WAVEFORMGENTERATOR_STR));
	DeviceDeinit(&pDev->device);
}

