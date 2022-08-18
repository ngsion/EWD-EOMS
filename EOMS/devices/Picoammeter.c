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
static int Start(Device *pDev)
{
	Picoammeter *pMeter = (Picoammeter *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;

		status = viPrintf(session, "*RST\n");
	//	status = viPrintf(session, ":SENS1:CURR:RANG 2e-2\n");
		status = viPrintf(session, ":FORM:ELEM CURR1\n");
		status = viPrintf(session, ":SOUR1:VOLT:RANG 30\n");
		status = viPrintf(session, ":SENS1:CURR:NPLC 1\n");

		int max = 30;
		int min = 0;
		int step = 2;
		for (int current = min; current <= max; current += step)
		{

			status = viPrintf(session, ":SOUR1:VOLT %d\n", current);
			status = viPrintf(session, ":OUTP1 ON\n");

			Delay(0.01);
			
			status = viPrintf(session, ":READ?\n");
			unsigned char buffer[14];
			memset(buffer, 0, 14);
			ViUInt32 retCount;
			status = viRead(session, buffer, 14, &retCount);
			if (status < VI_SUCCESS)
			{
				log_error("Error reading a response from the device %d.\n", session);
			}
			else
			{
			
				int num;
			    double value;
			
			//	log_info("instrument %d return %d is: %*s\n", session, retCount,retCount, buffer);
				num = Scan (buffer, "%s>%f", &value);
			
				log_info("instrument  %d volt %dV return is: %f nA\n", session,current, value*1000000000);
			}

			Delay(1);
		}
	}
	else
	{
		log_error("Picoammeter SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
	}

	return 0;
}

static int SetAttribute(struct Device *pDev)
{
	Picoammeter *pMeter = (Picoammeter *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{
		log_info("Picoammeter SetAttribute");
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
		log_error("Picoammeter SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
	}
	return 0;
}
static int Stop(Device *pDev)
{
	Picoammeter *pMeter = (Picoammeter *)pDev;

	if (NULL != pMeter->device.pInstr && pMeter->device.pInstr->status >= Instrument_Status_Open)
	{

		log_info("Picoammeter Stops");
		ViStatus status;
		ViSession session = pMeter->device.pInstr->session;
		status = viPrintf(session, ":OUTP1 OFF\n");
		status = viPrintf(session, "*RST\n");
	}
	else
	{
		log_error("Picoammeter SetAttribute failed null %d ", NULL == pMeter->device.pInstr);
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
}
void PicoammeterDeinit(Picoammeter *pDev)
{
	memcpy(pDev->device.name, "Picoammeter", sizeof("Picoammeter"));
	pDev->device.pInstr = NULL;
}
