//==============================================================================
//
// Title:		Measurement.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 15:35:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <visa.h>
#include "Measurement.h"
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int Start(Measurement * pDev){

   LOG_INFO("Measurement starts");
   return 0;
}
static int Stop(Measurement * pDev){
   LOG_INFO("Measurement Stops");
   return 0;
}

 static int DoMeasureWithCommand(struct Measurement * pDev, void * inData, void * outData)
 {
	LOG_INFO("Measurement DoMeasureWithCommand");
    return 0;
 }
//==============================================================================
// Global variables

void MeasurementInit(Measurement * pDev)
{
	if(NULL == pDev)
	{
		return;
	}
	pDev->instrumentFlag = Instrument_Unknown;
    pDev->pInstr = NULL;
	pDev->jobId = 0;
	pDev->Start = Start;
	pDev->Stop = Stop;
	pDev->isCollector = false;
	pDev->DoMeasureWithCommand = DoMeasureWithCommand;
	pDev->pDataQueue = QueueAllocInit();

}
void MeasurementDeinit(Measurement * pDev)
{
	pDev->instrumentFlag = Instrument_Unknown; 
	pDev->pInstr = NULL;
	QueueDelloc(pDev->pDataQueue);
}
