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
		LOG_INFO("before viPrintf %f",*pVolt);
		status = viPrintf(session, ":SOUR1:VOLT %0.2f\n", *pVolt);
		LOG_INFO("after viPrintf");
		
	}
	else
	{
		LOG_ERROR("Picoammeter DoWithCommand failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
    Picoammeter *pMeter = (Picoammeter *)functionData;
	int index = 0;
	for( index = 0; index <= 15; index++)
	{
		float volt = index *  2;
		pMeter->device.DoWithCommand(pMeter,&volt,NULL);
		Delay(1);
	}
	for( index = 0; index <= 15; index++)
	{
		float volt = 30 - index *  2;
		pMeter->device.DoWithCommand(pMeter,&volt,NULL);
		Delay(1);
	}
	LOG_INFO("Picoammeter ThreadFunction end");
	pMeter->device.Stop(pMeter);
	return 0;
}


static int Start(Device *pDev)
{
	if (!pDev)
	{
		LOG_ERROR("error in Picoammeter start");
		return -1;
	}
	ViStatus status = VI_SUCCESS; 
	Picoammeter *pMeter = (Picoammeter *)pDev;
	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		LOG_INFO("Picoammeter starts");
		
		ViSession session = pMeter->device.pInstr->session;
        status = viPrintf(session, ":SOUR1:VOLT 0\n");
		// status = viPrintf(session, ":SOUR1:VOLT:STAR 0\n");
		// status = viPrintf(session, ":SOUR1:VOLT:STOP 10\n");
		// status = viPrintf(session, ":SOUR1:VOLT:STEP 1\n");
		// status = viPrintf(session, ":SOUR1:VOLT:MODE SWE\n"); 
		// status = viPrintf(session, ":SOUR1:VOLT:MODE LIST\n");
		//  status = viPrintf(session, ":SOUR1:LIST:VOLT 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,30,28,26,24,22,20,18,16,14,12,10,8,6,4,2,0\n");
		// status = viPrintf(session, ":SOUR1:SWE:RANG AUTO\n");
		// status = viPrintf(session, ":SOUR1:SWE:SPAC LIN\n");
		// status = viPrintf(session, ":TRIG:COUN 10\n");
	 	//status = viPrintf(session, ":TRIG:COUN 32\n");
	    // status = viPrintf(session, ":SOUR1:DELay 0.1\n");
		
		status = viPrintf(session, ":SOUR1:VOLT:RANG:AUTO ON\n");  
		status = viPrintf(session, ":OUTP1 ON\n");

		CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,ThreadFunction, pDev, NULL);
				
	}
	else
	{
		LOG_ERROR("Picoammeter Start failed null %d ", NULL == pMeter->device.pInstr);
	}
if (status < VI_SUCCESS)
	{
		LOG_ERROR("status is %d.", status);
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
	pDev->device.instrumentFlag = Instrument_Picoammeter; 
	pDev->SetAttribute = SetAttribute;
	pDev->device.Start = Start;
	pDev->device.Stop = Stop;
	pDev->device.DoWithCommand = DoWithCommand;

}
void PicoammeterDeinit(Picoammeter *pDev)
{
	pDev->device.instrumentFlag = Instrument_Picoammeter;   
	DeviceDeinit(&pDev->device);
}
