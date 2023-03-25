#include <userint.h>

//==============================================================================
//
// Title:		LCRSet.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-25 at 16:22:28 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LCRSet.h"

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

int CVICALLBACK OnLCRSaveBtn(int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:

		break;
	}
	return 0;
}

int CVICALLBACK OnPanelLCRSet(int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_GOT_FOCUS:

		break;
	case EVENT_LOST_FOCUS:

		break;
	case EVENT_CLOSE:
		DiscardPanel(panel);
		break;
	}
	return 0;
}
