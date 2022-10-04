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

#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "EOMS.h"
#include "toolbox.h"
#include "EOMSystem.h"
#include "Queue.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN The main entry-point function.
int main(int argc, char *argv[])
{
	int error = 0;

	System.Init(0);

	/* initialize and load resources */
	nullChk(InitCVIRTE(0, argv, 0));
	errChk(panelHandle = LoadPanel(0, "EOMS.uir", PANEL));

	/* display the panel and run the user interface */
	errChk(DisplayPanel(panelHandle));
	errChk(RunUserInterface());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel(panelHandle);

	System.Shutdown(0);
	return 0;
}

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
		SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,TRUE);
		SetCtrlAttribute(panelHandle, PANEL_STRIPCHART_TOP, ATTR_SCROLL_MODE, VAL_CONTINUOUS);
		SetCtrlAttribute(panelHandle, PANEL_STRIPCHART_BOTTOM, ATTR_SCROLL_MODE, VAL_CONTINUOUS);
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
		SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,FALSE);
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
        Queue* qu = QueueAllocInit();
		qu->Push(qu,0.4);
		qu->Push(qu,0.5);
		
		LOG_INFO("queeu size %d",qu->size);
		double data;
		qu->Pop(qu,&data);
		   LOG_INFO("queeu size %d , data is %f",qu->size,data);
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
				if (0 == strcmp(MeasureMgr.pMeasureArray[i]->name, kDEVICE_LCRMETER_STR))
				{
					double oneData = 0;
					if (true == MeasureMgr.pMeasureArray[i]->pDataQueue->Pop(MeasureMgr.pMeasureArray[i]->pDataQueue, &oneData))
					{
						LOG_INFO("queeu size %d , data is %f",MeasureMgr.pMeasureArray[i]->pDataQueue->size,oneData); 
						PlotStripChartPoint(panelHandle, PANEL_STRIPCHART_TOP, oneData);
					}
				}
				else if (0 == strcmp(MeasureMgr.pMeasureArray[i]->name, kDEVICE_PICOAMMETER_STR))
				{
					double oneData = 0;
					if (true == MeasureMgr.pMeasureArray[i]->pDataQueue->Pop(MeasureMgr.pMeasureArray[i]->pDataQueue, &oneData))
					{
						LOG_INFO("queeu size %d , data is %f",MeasureMgr.pMeasureArray[i]->pDataQueue->size,oneData); 
						PlotStripChartPoint(panelHandle, PANEL_STRIPCHART_BOTTOM, oneData);
					}
				}
			}
		}

		break;
	}
	return 0;
}
