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

#include <utility.h>
#include <ansi_c.h>
#include "DeviceMgr.h"
#include "Picoammeter.h"
#include "WaveformGenerator.h"
#include "logger.h"
#include "LCRMeter.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static Device *defaultDeviceArray[DEVICE_MAX_NUM];
static int threadId = 0;

//==============================================================================
// Static functions
static int Init(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		defaultDeviceArray[i] = NULL;
	}

	defaultDeviceArray[0] = (Device *)malloc(sizeof(Picoammeter));
	PicoammeterInit((Picoammeter *)defaultDeviceArray[0]);
	defaultDeviceArray[0]->isSignal = true;

	defaultDeviceArray[1] = (Device *)malloc(sizeof(WaveformGenerator));
	WaveformGeneratorInit((WaveformGenerator *)defaultDeviceArray[1]);
	defaultDeviceArray[1]->isSignal = false;

	defaultDeviceArray[2] = (Device *)malloc(sizeof(LCRMeter));
	LCRMeterInit((LCRMeter *)defaultDeviceArray[2]);
	defaultDeviceArray[2]->isSignal = false;

	return 0;
}

static int AfterInit(int x)
{
	int i = 0;
	for (i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != defaultDeviceArray[i])
		{
			if (0 == strcmp(defaultDeviceArray[i]->name, DEVICE_PICOAMMETER_STR))
			{
				Picoammeter *pMeter = defaultDeviceArray[i];
				pMeter->SetAttribute(pMeter);
			}

			defaultDeviceArray[i]->QueryID(defaultDeviceArray[i]);
		}
	}

	return 0;
}

static int CVICALLBACK ThreadFunction(void *functionData)
{
 	Delay(3);
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != defaultDeviceArray[i] && true == defaultDeviceArray[i]->isSignal)
		{
			LOG_INFO("before start");
			defaultDeviceArray[i]->Start(defaultDeviceArray[i]);
			LOG_INFO("after start");
		}
	}
	int index = 0;
	for( index = 0; index <= 15; index++)
	{
		float volt = index *  2;
		defaultDeviceArray[0]->DoWithCommand(defaultDeviceArray[0],&volt,NULL);
		Delay(0.5);
	}
	for( index = 0; index <= 15; index++)
	{
		float volt = 30 - index *  2;
		defaultDeviceArray[0]->DoWithCommand(defaultDeviceArray[0],&volt,NULL);
		Delay(0.5);
	}
	
		 /* Wait for the thread functions to finish executing */
	 CmtWaitForThreadPoolFunctionCompletion(DEFAULT_THREAD_POOL_HANDLE,threadId,0);
	 /* Release thread functions */
	 CmtReleaseThreadPoolFunctionID(DEFAULT_THREAD_POOL_HANDLE, threadId);

	return 0;
}

static int Start(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != defaultDeviceArray[i])
		{
			defaultDeviceArray[i]->Reset(defaultDeviceArray[i]);
		}
	}


	//ThreadFunction(NULL);
	 CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,ThreadFunction, NULL,&threadId);


	return 0;
}
static int Stop(int x)
{
	for (int i = 0; i < DEVICE_MAX_NUM; i++)
	{
		if (NULL != defaultDeviceArray[i] && true == defaultDeviceArray[i]->isSignal)
		{
			defaultDeviceArray[i]->Stop(defaultDeviceArray[i]);
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
