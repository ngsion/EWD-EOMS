//==============================================================================
//
// Title:		EOMS
// Purpose:		A short description of the application.
//
// Created on:	2022-08-12 at 15:50:59 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "Excel.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "EOMS.h"
#include "toolbox.h"
#include "EOMSystem.h"
#include "Queue.h"
#include "Map.h"
#include "SettingMgr.h"
#include "UIMgr.h"

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

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB(int panel, int event, void *callbackData,
						int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
	{
		if (true == System.isWorking)
		{
			System.Stop(0);
		}
		SetCtrlAttribute(panel, PANEL_TIMER, ATTR_ENABLED, FALSE);
		System.Shutdown(0);
		QuitUserInterface(0);
	}

	return 0;
}

int CVICALLBACK onOKBtb(int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		if (true == System.isWorking)
			return 0;

		//	SetAxisScalingMode( panel, PANEL_STRIPCHART_TOP, VAL_LEFT_YAXIS, VAL_AUTOSCALE, 4000, 10000);

		//	SetAxisScalingMode( panel, PANEL_STRIPCHART_BOTTOM, VAL_LEFT_YAXIS, VAL_AUTOSCALE, 4000, 10000);

		ClearStripChart(panel, PANEL_STRIPCHART_TOP);
		ClearStripChart(panel, PANEL_STRIPCHART_BOTTOM);
		SetCtrlAttribute(panel, PANEL_TIMER, ATTR_ENABLED, TRUE);
		SetCtrlAttribute(panel, PANEL_STRIPCHART_TOP, ATTR_SCROLL_MODE, VAL_CONTINUOUS);
		SetCtrlAttribute(panel, PANEL_STRIPCHART_BOTTOM, ATTR_SCROLL_MODE, VAL_CONTINUOUS);
		System.Start(0);
		break;
	}
	return 0;
}

int CVICALLBACK onStopBtn(int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		SetCtrlAttribute(panel, PANEL_TIMER, ATTR_ENABLED, FALSE);
		System.Stop(0);
		break;
	}
	return 0;
}

int CVICALLBACK OnIDBtn(int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		SetCtrlAttribute(panel, PANEL_TIMER, ATTR_ENABLED, FALSE);
		System.Stop(0);

		UI.ShowEntry(0);
	}
	break;
	}
	return 0;
}

int CVICALLBACK UpdateTimer(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_TIMER_TICK:

		for (int i = 0; i < MEASURE_MAX_NUM; i++)
		{
			if (NULL != MeasureMgr.pMeasureArray[i])
			{
				if (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_LCRMeter)
				{
					double oneData = 0;
					{
						int size = MeasureMgr.pMeasureArray[i]->pDataQueue->size;
						while (size > 0)
						{
							MeasureMgr.pMeasureArray[i]->pDataQueue->Pop(MeasureMgr.pMeasureArray[i]->pDataQueue, &oneData);
							PlotStripChartPoint(panel, PANEL_STRIPCHART_TOP, oneData);

							--size;
						}
					}
				}
				else if (MeasureMgr.pMeasureArray[i]->instrumentFlag == Instrument_Picoammeter)
				{
					double oneData = 0;

					int size = MeasureMgr.pMeasureArray[i]->pDataQueue->size;
					while (size > 0)
					{
						MeasureMgr.pMeasureArray[i]->pDataQueue->Pop(MeasureMgr.pMeasureArray[i]->pDataQueue, &oneData);
						PlotStripChartPoint(panel, PANEL_STRIPCHART_BOTTOM, oneData);
						--size;
					}
				}
			}
		}

		break;
	}
	return 0;
}
