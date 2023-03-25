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

int CVICALLBACK OnPanelWaveSet(int panel, int event, void *callbackData,
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

int CVICALLBACK OnWaveSetSaveBtn(int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
    case EVENT_COMMIT:

        break;
    }
    return 0;
}
