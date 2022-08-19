//==============================================================================
//
// Title:		MeasurementMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-18 at 15:36:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "MeasurementMgr.h"
#include "PicoammeterMeasure.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static PicoammeterMeasure picoaMeasure;
//==============================================================================
// Static functions
static int Start(int x)
{
   ((Measurement*) &picoaMeasure)->Start((Measurement*) &picoaMeasure);
    
	return 0;
}
static int Stop(int x)
{
     ((Measurement*) &picoaMeasure)->Stop((Measurement*) &picoaMeasure);
	return 0;
}
static int Init(int x)
{
    PicoammeterMeasureInit(&picoaMeasure);
	return 0;
}

static int Shutdown(int x)
{
    PicoammeterMeasureDeinit(&picoaMeasure);
	return 0;
}

//==============================================================================
// Global functions

//==============================================================================
// Global variables

MeasurementMgr MeasureMgr = {
	.pPicoammeterMeasure =(Measurement*)  &picoaMeasure,
	.Init = Init,
	.Start = Start,
	.Stop = Stop,
    .Shutdown = Shutdown
};
