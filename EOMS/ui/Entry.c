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
static bool firstGetFoucus = false;

//==============================================================================
// Static functions
static int updateStrings(int panel);
static int updateLED(int panel);

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int ConnectDevice(int panel, int devIndex)
{
	Setting *pSet = SetMgr.FindWithInstrFlag(devIndex);
	Instrument *pInstr = InstrMgr.GetInstrByIndex(pSet->lastInstrIndex);

	Device *pMeter = DevMgr.FindWithInstrFlag(devIndex);

	if (NULL != pInstr && pMeter->type == pInstr->type)
	{
		pMeter->pInstr = pInstr;
		if (0 == pMeter->Connect(pMeter))
		{
			pMeter->QueryID(pMeter);
		}
	}
	else
	{
		pMeter->pInstr = NULL;
	}
	updateLED(panel);
	updateStrings(panel);
	return 0;
}

int CVICALLBACK OnOkBtn(int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{

		int index = Instrument_Picoammeter;
		for (; index < Instrument_WaveformGenerator; index++)
		{
			Setting *pSet = SetMgr.FindWithInstrFlag(index);
			GetCtrlVal(panel, PANEL_CHECKBOX_PICO_SRC + index - Instrument_Picoammeter, &pSet->isSignal);
		}

		for (index = Instrument_Picoammeter; index < Instrument_LCRMeter; index++)
		{
			Setting *pSet = SetMgr.FindWithInstrFlag(index);
			GetCtrlVal(panel, PANEL_CHECKBOX_PICO_DATA + index - Instrument_Picoammeter, &pSet->isCollector);
		}

		UI.ShowGraph(0);
	}

	break;
	}
	return 0;
}

int updateStrings(int panel)
{

	for (int index = Instrument_Picoammeter; index <= Instrument_Admesy; index++)
	{
		Device *pMeter = DevMgr.FindWithInstrFlag(index);

		if (NULL != pMeter->pInstr)
		{
			ResetTextBox(panel, PANEL_TEXTBOX_PICO + index - Instrument_Picoammeter, pMeter->pInstr->identifier);
		}
		else
		{
			ResetTextBox(panel, PANEL_TEXTBOX_PICO + index - Instrument_Picoammeter, "");
		}
	}

	return 0;
}

int updateLED(int panel)
{
	for (int index = Instrument_Picoammeter; index <= Instrument_Admesy; index++)
	{
		Device *pMeter = DevMgr.FindWithInstrFlag(index);

		if (NULL != pMeter->pInstr && pMeter->pInstr->status >= Instrument_Status_Connected)
		{

			SetCtrlVal(panel, PANEL_LED_PICO + index - Instrument_Picoammeter, 1);
		}
		else
		{
			SetCtrlVal(panel, PANEL_LED_PICO + index - Instrument_Picoammeter, 0);
		}
	}

	return 0;
}

int updateRingControls(int panel)
{
	for (int index = Instrument_Picoammeter; index <= Instrument_Admesy; index++)
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(index);
		int cur = PANEL_RING_PICO + index - Instrument_Picoammeter;
		int number = 0;
		GetNumListItems(panel, cur, &number);
		if (number != InstrMgr.instrumentsCount)
		{
			ClearListCtrl(panel, cur);
			InstrumentListNode *pHead = *InstrMgr.plist;
			int index = 0;
			int count = 1;

			index = -1;
			++count;
			while (pHead != NULL)
			{
				InstrumentListNode *pNode = pHead;
				InsertListItem(panel, cur, index, pNode->pInstr->address, count);
				++count;
				pHead = pNode->next;
			}
			SetCtrlIndex(panel, cur, pSet->lastInstrIndex); // Based on index
		}
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
		if (!firstGetFoucus)
		{
			//InstrMgr.Scan(0);
			//updateRingControls(panel);

			firstGetFoucus = true;
			int index = Instrument_Picoammeter;
			for (; index < Instrument_WaveformGenerator; index++)
			{
				Setting *pSet = SetMgr.FindWithInstrFlag(index);
				SetCtrlVal(panel, PANEL_CHECKBOX_PICO_SRC + index - Instrument_Picoammeter, pSet->isSignal);
			}

			for (index = Instrument_Picoammeter; index < Instrument_LCRMeter; index++)
			{
				Setting *pSet = SetMgr.FindWithInstrFlag(index);
				SetCtrlVal(panel, PANEL_CHECKBOX_PICO_DATA + index - Instrument_Picoammeter, pSet->isCollector);
			}
		}
	}
	break;

	case EVENT_CLOSE:
	{
		firstGetFoucus = false;
		// if (true == System.isWorking)
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

int CVICALLBACK OnRefreshBtn(int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
	case EVENT_COMMIT:
		InstrMgr.Scan(0);
		updateRingControls(panel);
		updateLED(panel);
		break;
	}
	return 0;
}

int CVICALLBACK OnPicoRing(int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
	case EVENT_VAL_CHANGED:
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(Instrument_Picoammeter);
		GetCtrlIndex(panel, PANEL_RING_PICO, &pSet->lastInstrIndex);
		ConnectDevice(panel, Instrument_Picoammeter);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnLCRRing(int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_VAL_CHANGED:
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(Instrument_LCRMeter);
		GetCtrlIndex(panel, PANEL_RING_LCR, &pSet->lastInstrIndex);
		ConnectDevice(panel, Instrument_LCRMeter);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnWaveRing(int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_VAL_CHANGED:
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
		GetCtrlIndex(panel, PANEL_RING_WAVE, &pSet->lastInstrIndex);
		ConnectDevice(panel, Instrument_WaveformGenerator);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnAdmesy(int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_VAL_CHANGED:
	{
		Setting *pSet = SetMgr.FindWithInstrFlag(Instrument_Admesy);
		GetCtrlIndex(panel, PANEL_RING_WAVE, &pSet->lastInstrIndex);
		ConnectDevice(panel, Instrument_Admesy);
	}
	break;
	}
	return 0;
}

int CVICALLBACK OnPicoSet(int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		UI.ShowPICOSet(0);
		break;
	}
	return 0;
}

int CVICALLBACK OnLCRSet(int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		UI.ShowLCRSet(0);
		break;
	}
	return 0;
}

int CVICALLBACK OnWAVESet(int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		UI.ShowWaveSet(0);
		break;
	}
	return 0;
}
