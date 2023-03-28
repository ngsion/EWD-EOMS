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
static double lastX = -1;
static double lastY = -1;
static bool shouldchange = false;
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

int CVICALLBACK OnPanelCV(int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{

	case EVENT_CLOSE:
	{
//		if (true == System.isWorking)
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

int CVICALLBACK OnStartCVBtn(int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:

//		if (true == System.isWorking)
			//return 0;

	//	SetPlotAttribute(panel, PANEL_GRAPH,  ATTR_LINE_STYLE, VAL_SOLID);  
		
	///	SetAxisScalingMode(panel, PANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, 4000, 10000);

		DeleteGraphPlot(panel, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);

		SetCtrlAttribute(panel, PANEL_TIMER_CV, ATTR_ENABLED, TRUE);

		shouldchange = false;

		System.Start(0);

		break;
	}
	return 0;
}

int CVICALLBACK OnCVBack(int panel, int control, int event,
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

int CVICALLBACK UpdateTimerCV(int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_TIMER_TICK:
	{
		Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_LCRMeter);
		if (NULL != pMeasure)
		{

			int size = pMeasure->pDataQueue->size;
			double oneData = 0;
			double inData = 0;
			while (size > 0)
			{
				pMeasure->pDataQueue->Pop(pMeasure->pDataQueue, &oneData);
				pMeasure->pInDataQueue->Pop(pMeasure->pInDataQueue, &inData);

				if (-1 == lastX && -1 == lastY)
				{
				}
				else
				{
					if (lastX >= 30)
					{
						shouldchange = true;
					}
					if (shouldchange)
					{
						PlotLine(panel, PANEL_GRAPH, lastX, lastY, inData, oneData, VAL_DK_RED);
					}
					else
					{
						PlotLine(panel, PANEL_GRAPH, lastX, lastY, inData, oneData, VAL_DK_BLUE);
					}
				}
				lastX = inData;
				lastY = oneData;
				--size;
			}
		}
	}
	break;
	}
	return 0;
}
