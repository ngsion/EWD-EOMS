#include <userint.h>

//==============================================================================
//
// Title:		CVGraph.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-10 at 21:27:46 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "CVGraph.h"
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


int CVICALLBACK OnPanelCV (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
				{
		if (true == System.isWorking)
		{
			System.Stop(0);
		}
		SetCtrlAttribute(panel, PANEL_TIMER_CV, ATTR_ENABLED, FALSE);
		System.Shutdown(0);
		QuitUserInterface(0);
	}


			break;
	}
	return 0;
}

int CVICALLBACK OnStartCVBtn (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
		if (true == System.isWorking)
			return 0;

		SetAxisScalingMode( panel, PANEL_STRIPCHART_CV, VAL_LEFT_YAXIS, VAL_MANUAL, 4000, 10000);  

		ClearStripChart(panel, PANEL_STRIPCHART_CV);

		SetCtrlAttribute(panel, PANEL_TIMER_CV, ATTR_ENABLED, TRUE);
		SetCtrlAttribute(panel, PANEL_STRIPCHART_CV, ATTR_SCROLL_MODE, VAL_CONTINUOUS);

		System.Start(0);

		break;

	
	}
	return 0;
}

int CVICALLBACK OnCVBack (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				SetCtrlAttribute(panel, PANEL_TIMER_CV, ATTR_ENABLED, FALSE);
		System.Stop(0);

		UI.ShowEntry(0);

			break;
	}
	return 0;
}

int CVICALLBACK UpdateTimerCV (int panel, int control, int event,
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
					if (true == MeasureMgr.pMeasureArray[i]->pDataQueue->Pop(MeasureMgr.pMeasureArray[i]->pDataQueue, &oneData))
					{
						LOG_INFO("queeu size %d , data is %f", MeasureMgr.pMeasureArray[i]->pDataQueue->size, oneData);
						PlotStripChartPoint(panel, PANEL_STRIPCHART_CV, oneData);
					}
				}
			
			}
		}
			break;
	}
	return 0;
}
