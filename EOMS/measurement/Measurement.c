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
#include "log.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int Start(Measurement * pDev){

   log_info("Measurement starts");
   return 0;
}
static int Stop(Measurement * pDev){
   log_info("Measurement Stops");
   return 0;
}

 static int DoCollect(struct Measurement * pDev, void * inData, void * outData)
 {
	log_info("Measurement DoCollect");
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
    pDev->pInstr = NULL;
	pDev->Start = Start;
	pDev->Stop = Stop;
	pDev->DoCollect = DoCollect;
}
void MeasurementDeinit(Measurement * pDev)
{
	
	pDev->pInstr = NULL;
}
