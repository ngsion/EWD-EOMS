#include <cvirte.h>
#include <userint.h>

//==============================================================================
//
// Title:		Entry.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-07 at 16:10:15 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Entry.h"
#include "EOMSystem.h"
#include "SettingMgr.h"
#include "Stack.h"
#include "UIMgr.h"
#include "DeviceMgr.h"

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

int CVICALLBACK OnRadioWave(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		SetCtrlVal(panel, PANEL_RADIOBUTTON_PICO, 0);
		SetCtrlVal(panel, PANEL_RADIOBUTTON_LCR, 0);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnRadioLCR(int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		SetCtrlVal(panel, PANEL_RADIOBUTTON_PICO, 0);
		SetCtrlVal(panel, PANEL_RADIOBUTTON_WAVE, 0);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnRadioPico(int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		SetCtrlVal(panel, PANEL_RADIOBUTTON_LCR, 0);
		SetCtrlVal(panel, PANEL_RADIOBUTTON_WAVE, 0);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnOkBtn(int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{
		int lcrSource = 0;
		int picoSource = 0;
		int waveSource = 0;
		GetCtrlVal(panel, PANEL_RADIOBUTTON_LCR, &lcrSource);
		GetCtrlVal(panel, PANEL_RADIOBUTTON_WAVE, &waveSource);
		GetCtrlVal(panel, PANEL_RADIOBUTTON_PICO, &picoSource);
		if (lcrSource)
		{
			SetMgr.signal = Signal_LCRMeter;
		}
		else if (picoSource)
		{
			SetMgr.signal = Signal_Picoammieter;
		}
		else if (waveSource)
		{
			SetMgr.signal = Signal_WaveformGenerator;
		}

		SetMgr.data = Data_None;
		int picoData = 0;
		int lcrData = 0;
		GetCtrlVal(panel, PANEL_CHECKBOX_PICO, &picoData);
		GetCtrlVal(panel, PANEL_CHECKBOX_LCR, &lcrData);
		if (lcrData)
		{
			SetMgr.data |= Data_Cp;
			SetMgr.data |= Data_D;
		}
		if (picoData)
		{
			SetMgr.data |= Data_Current;
		}



		System.LoadSettings(0);


		if (Signal_Picoammieter == SetMgr.signal)
		{
			UI.ShowLCGraph(0);
		}
		else if (Signal_LCRMeter == SetMgr.signal)
		{
			UI.ShowCVGraph(0);
		}
		else
		{
			UI.ShowGraph(0);
		}
	}

	break;
	}
	return 0;
}

int updateStrings(int panel)
{

	Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
	if (NULL != pMeter && NULL != pMeter->pInstr)
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_PICO, pMeter->pInstr->identifier);
	}
	else
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_PICO, "");
	}
	pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
	if (NULL != pMeter && NULL != pMeter->pInstr)
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_LCR, pMeter->pInstr->identifier);
	}
	else
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_LCR, "");
	}
	pMeter = DevMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
	if (NULL != pMeter && NULL != pMeter->pInstr)
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_WAVE, pMeter->pInstr->identifier);
	}
	else
	{
		SetCtrlVal(panel, PANEL_TEXTBOX_WAVE, "");
	}
	return 0;
}

int updateLED(int panel)
{
	if (SetMgr.online & Online_Picoammieter)
	{
		SetCtrlVal(panel, PANEL_LED_PICO, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_PICO, 0);
	}

	if (SetMgr.online & Online_LCRMeter)
	{
		SetCtrlVal(panel, PANEL_LED_LCR, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_LCR, 0);
	}
	if (SetMgr.online & Online_WaveformGenerator)
	{
		SetCtrlVal(panel, PANEL_LED_WAVE, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_WAVE, 0);
	}
	return 0;
}

int CVICALLBACK OnPanel(int panel, int event, void *callbackData,
						int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_GOT_FOCUS:
	{
		updateLED(panel);
		updateStrings(panel);
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
		System.Shutdown(0);
		QuitUserInterface(0);
	}

	break;
	}
	return 0;
}
