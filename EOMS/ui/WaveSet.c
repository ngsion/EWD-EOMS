#include <userint.h>

//==============================================================================
//
// Title:		WaveSet.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-25 at 16:29:49 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "WaveSet.h"
#include "SettingMgr.h"
#include "WaveformSetting.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static bool firstGetFoucus = false;
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

int CVICALLBACK OnPanelWaveSet(int panel, int event, void *callbackData,
                               int eventData1, int eventData2)
{
    switch (event)
    {
    case EVENT_GOT_FOCUS:
    {
        if (!firstGetFoucus)
        {
            firstGetFoucus = true;
            WaveformSetting *pSet = SetMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
            SetCtrlVal(panel, PANEL_WS_NUMERIC_FREQUENCY, pSet->frequecy);
            SetCtrlVal(panel, PANEL_WS_NUMERIC_HIGH, pSet->high);
            SetCtrlVal(panel, PANEL_WS_NUMERIC_LOW, pSet->low);
            SetCtrlVal(panel, PANEL_WS_NUMERIC_CH1OFFSET, pSet->offset1);
            SetCtrlVal(panel, PANEL_WS_NUMERIC_CH2OFFSET, pSet->offset2);
        }
    }
    break;
    case EVENT_LOST_FOCUS:

        break;
    case EVENT_CLOSE:
    {
        firstGetFoucus = false;
        DiscardPanel(panel);
    }
    break;
    }
    return 0;
}

int CVICALLBACK OnWaveSetSaveBtn(int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
    case EVENT_COMMIT:
    {
        WaveformSetting *pSet = SetMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
        GetCtrlVal(panel, PANEL_WS_NUMERIC_FREQUENCY, &pSet->frequecy);
        GetCtrlVal(panel, PANEL_WS_NUMERIC_HIGH, &pSet->high);
        GetCtrlVal(panel, PANEL_WS_NUMERIC_LOW, &pSet->low);
        GetCtrlVal(panel, PANEL_WS_NUMERIC_CH1OFFSET, &pSet->offset1);
        GetCtrlVal(panel, PANEL_WS_NUMERIC_CH2OFFSET, &pSet->offset2);
         DiscardPanel(panel);
    }
    break;
    }
    return 0;
}
