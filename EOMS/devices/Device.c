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

#include "Device.h"
#include <string.h>
#include "../logger/log.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int Start(Device * pDev){
   log_info("Device starts");
   return 0;
}
static int Stop(Device * pDev){
   log_info("Device Stops");
   return 0;
}
static int DoFire(struct Device * pDev, void * inData, void * outData)
{
   log_info("Device DoFire");
   return 0;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions

void DeviceInit(Device * pDev)
{
	if(NULL == pDev)
	{
		return;
	}
	memcpy(pDev->name,"Device",sizeof("Device"));
	pDev->pInstr = NULL;
	pDev->Start = Start;
	pDev->Stop = Stop;
	pDev->DoFire = DoFire;
}
void DeviceDeinit(Device * pDev)
{
	memcpy(pDev->name,"Device",sizeof("Device"));
	pDev->pInstr = NULL;
}
