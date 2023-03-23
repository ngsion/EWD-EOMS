#include <userint.h>

//==============================================================================
//
// Title:		PicoSet.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-21 at 11:22:30 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "PicoSet.h"
#include "PicoSetting.h"
#include "SettingMgr.h"
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

int CVICALLBACK OnNextBtn(int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		PicoSetting *pSet = SetMgr.FindWithInstrFlag(Instrument_Picoammeter);
		GetCtrlVal(panel, PANEL_PSET_NUMERIC_VMAX, &pSet->VMax);
		GetCtrlVal(panel, PANEL_PSET_NUMERIC_VMIN, &pSet->VMin);
		GetCtrlVal(panel, PANEL_PSET_NUMERIC_VSPAN, &pSet->VSpan);
		GetCtrlVal(panel, PANEL_PSET_NUMERIC_INTERVAL, &pSet->MInterval);
		GetCtrlVal(panel, PANEL_PSET_STRING_BATCH, pSet->setting.batchNo);
	}
	break;
	}

	return 0;
}

int CVICALLBACK OnPanelPicoSet(int panel, int event, void *callbackData,
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
