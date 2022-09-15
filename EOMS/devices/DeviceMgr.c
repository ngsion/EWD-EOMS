//==============================================================================
//
// Title:		DeviceMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 13:42:24 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "DeviceMgr.h"
#include "Picoammeter.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static Device * defaultDeviceArray[DEVICE_MAX_NUM];
//==============================================================================
// Static functions
static int Init(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		defaultDeviceArray[i] = NULL;
	}
	
    defaultDeviceArray[0] = (Device*) malloc(sizeof(Picoammeter));
	PicoammeterInit((Picoammeter*)defaultDeviceArray[0] );
	return 0;
}

static int AfterInit(int x)
{
	if(	NULL != defaultDeviceArray[0] )
	{
		Picoammeter * pMeter = defaultDeviceArray[0];
		pMeter->SetAttribute(pMeter);
	}
	
	return 0;
}

static int Start(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if(	NULL != defaultDeviceArray[i] && true == defaultDeviceArray[i].isSource){
			defaultDeviceArray[i] ->Start(defaultDeviceArray[i] );     
		}
    	
	}
    
	return 0;
}
static int Stop(int x)
{
		for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if(	NULL != defaultDeviceArray[i] ){
			defaultDeviceArray[i] ->Stop(defaultDeviceArray[i] );     
		}
    	
	}

	return 0;
}
static int Shutdown(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != defaultDeviceArray[i])
		{
			free(defaultDeviceArray[i]);
			defaultDeviceArray[i] = NULL;
		}
		
	}

	return 0;
}


//==============================================================================
// Global variables

DeviceMgr DevMgr = {
	.pDevArray = &defaultDeviceArray,
	.AfterInit = AfterInit,
	.Init = Init,
	.Shutdown = Shutdown,
	.Start = Start,
	.Stop = Stop

};
