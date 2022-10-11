#include <userint.h>

//==============================================================================
//
// Title:		LCGraph.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-10 at 20:58:38 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LCGraph.h"
#include "toolbox.h"
#include "EOMSystem.h"
#include "Queue.h"
#include "Map.h"
#include "SettingMgr.h"
#include "UIMgr.h"
#include "MeasurementMgr.h"

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

int CVICALLBACK OnStartBtn(int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		if (true == System.isWorking)
			return 0;

		SetAxisScalingMode(panel, PANEL_STRIPCHART, VAL_LEFT_YAXIS, VAL_MANUAL, -1000, 1500);

		ClearStripChart(panel, PANEL_STRIPCHART);

		SetCtrlAttribute(panel, PANEL_TIMER_LC, ATTR_ENABLED, TRUE);
		SetCtrlAttribute(panel, PANEL_STRIPCHART, ATTR_SCROLL_MODE, VAL_CONTINUOUS);

		System.Start(0);

		break;
	}
	return 0;
}

int CVICALLBACK OnBack(int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		SetCtrlAttribute(panel, PANEL_TIMER_LC, ATTR_ENABLED, FALSE);
		System.Stop(0);

		UI.ShowEntry(0);
		break;
	}
	return 0;
}

int CVICALLBACK OnPanelLC(int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_GOT_FOCUS:
	{
	}

	break;
	case EVENT_LOST_FOCUS:

		break;
	case EVENT_CLOSE:
	{
		if (true == System.isWorking)
		{
			System.Stop(0);
		}
		SetCtrlAttribute(panel, PANEL_TIMER_LC, ATTR_ENABLED, FALSE);
		System.Shutdown(0);
		QuitUserInterface(0);
	}

	break;
	}
	return 0;
}

int CVICALLBACK UpdateTimerLC(int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_TIMER_TICK:
	{
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_Picoammeter);

		if (NULL != pMeasure)
		{
			double oneData = 0;
			if (true == pMeasure->pDataQueue->Pop(pMeasure->pDataQueue, &oneData))
			{
				LOG_INFO("queeu size %d , data is %f", pMeasure->pDataQueue->size, oneData);
				PlotStripChartPoint(panel, PANEL_STRIPCHART, oneData);
			}
		}
	}
	break;
	}
	return 0;
}
