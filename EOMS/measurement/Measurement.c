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

 static int DoMeasureWithCommand(struct Measurement * pMea, void * inData, void * outData1, void * outData2)
 {
	LOG_INFO("Measurement DoMeasureWithCommand");
    return 0;
 }
//==============================================================================
// Global variables

void MeasurementInit(Measurement * pMea)
{
	if(NULL == pMea)
	{
		return;
	}
	pMea->instrumentFlag = Instrument_Unknown;
    pMea->pDev = NULL;
	pMea->pSet = NULL;
	pMea->isCollecting = false;
	pMea->Start = Start;
	pMea->Stop = Stop;
	pMea->DoMeasureWithCommand = DoMeasureWithCommand;
	pMea->pDataQueue = QueueAllocInit();
    pMea->pInDataQueue = QueueAllocInit();
}
void MeasurementDeinit(Measurement * pMea)
{
	pMea->instrumentFlag = Instrument_Unknown; 
	pMea->pDev = NULL;
	pMea->pSet = NULL;
	pMea->isCollecting = false;
	QueueDelloc(pMea->pDataQueue);
	QueueDelloc(pMea->pInDataQueue);
}
