//==============================================================================
//
// Title:		Admesy.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-11-07 at 9:53:33 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Admesy.h"
#include <utility.h>
#include <ansi_c.h>
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
void AdmesyInit(Admesy *pDev)
{
	if (NULL == pDev)
	{
		return;
	}
	DeviceInit(&pDev->device);
	pDev->device.instrumentFlag = Instrument_Admesy; 
	pDev->device.type = Instrument_Type_USB;

}
void AdmesyDeinit(Admesy *pDev)
{
	pDev->device.instrumentFlag = Instrument_Admesy; 
	DeviceDeinit(&pDev->device);
}
