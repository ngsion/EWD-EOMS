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
#include "SettingMgr.h"
#include "LCRSetting.h"
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
	{
		LCRSetting *pSet = SetMgr.FindWithInstrFlag(Instrument_Picoammeter);
		GetCtrlVal(panel, PANEL_LCRS_NUMERIC_LCRMAX, &pSet->VMax);
		GetCtrlVal(panel, PANEL_LCRS_NUMERIC_LCRMIN, &pSet->VMin);
		GetCtrlVal(panel, PANEL_LCRS_NUMERIC_LCRSTEP, &pSet->VSpan);
		GetCtrlVal(panel, PANEL_LCRS_NUMERIC_LCRINTERVAL, &pSet->MInterval);
		GetCtrlVal(panel, PANEL_LCRS_STRING_LCRBATCH, pSet->setting.batchNo);
	}
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
