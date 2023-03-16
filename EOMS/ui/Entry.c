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
int updateStrings(int panel);
int updateLED(int panel);

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int ConnectPico(int panel)
{
	int ringIdx;
	GetCtrlIndex(panel, PANEL_RING_PICO, &ringIdx);
	LOG_INFO("PICO INDEX %d", ringIdx);
	InstrumentListNode *pHead = *InstrMgr.plist;
	int index = 0;

	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		if (index == ringIdx)
		{
			Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
			pMeter->pInstr = pNode->pInstr;

			Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_Picoammeter);
			pMeasure->pInstr = pNode->pInstr;

			if (Instrument_Type_ASRL == pNode->pInstr->type)
			{
				if (-1 == pNode->pInstr->Open(pNode->pInstr))
				{
					LOG_ERROR("Error open %s", pNode->pInstr->address);
				}
				else
				{

					pMeter->SetAttribute(pMeter);

					pNode->pInstr->QueryID(pNode->pInstr);
					LOG_INFO("Init one instrument is %s, id %s", pNode->pInstr->address, pNode->pInstr->identifier);
				}
			}
			updateLED(panel);
			updateStrings(panel);
			return 0;
		}
		++index;
		pHead = pNode->next;
	}
	return -1;
}
int ConnectLCR(int panel)
{
	int ringIdx;
	GetCtrlIndex(panel, PANEL_RING_LCR, &ringIdx);
	LOG_INFO("LCR INDEX %d", ringIdx);
	InstrumentListNode *pHead = *InstrMgr.plist;
	int index = 0;

	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;

		if (index == ringIdx)
		{
			Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
			pMeter->pInstr = pNode->pInstr;

			Measurement *pMeasure = MeasureMgr.FindWithInstrFlag(Instrument_LCRMeter);
			pMeasure->pInstr = pNode->pInstr;

			if (Instrument_Type_GPIB == pNode->pInstr->type)
			{
				if (-1 == pNode->pInstr->Open(pNode->pInstr))
				{
					LOG_ERROR("Error open %s", pNode->pInstr->address);
				}
				else
				{
					pNode->pInstr->QueryID(pNode->pInstr);
					LOG_INFO("Init one instrument is %s, id %s", pNode->pInstr->address, pNode->pInstr->identifier);
				}
			}
			updateLED(panel);
			updateStrings(panel);
			return 0;
		}
		++index;
		pHead = pNode->next;
	}
	return -1;
}
int ConnectWave(int panel)
{
	int ringIdx;
	GetCtrlIndex(panel, PANEL_RING_WAVE, &ringIdx);
	LOG_INFO("wave INDEX %d", ringIdx);
	InstrumentListNode *pHead = *InstrMgr.plist;
	int index = 0;

	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;

		if (index == ringIdx)
		{
			Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
			pMeter->pInstr = pNode->pInstr;
			if (Instrument_Type_USB == pNode->pInstr->type)
			{
				if (-1 == pNode->pInstr->Open(pNode->pInstr))
				{
					LOG_ERROR("Error open %s", pNode->pInstr->address);
				}
				else
				{
					pNode->pInstr->QueryID(pNode->pInstr);
					LOG_INFO("Init one instrument is %s, id %s", pNode->pInstr->address, pNode->pInstr->identifier);
				}
				updateLED(panel);
				updateStrings(panel);

				return 0;
			}
		}
		++index;
		pHead = pNode->next;
	}
	return -1;
}

int ConnectAdmesy(int panel)
{
	int ringIdx;
	GetCtrlIndex(panel, PANEL_RING_ADMESY, &ringIdx);
	LOG_INFO("ADMESY INDEX %d", ringIdx);
	InstrumentListNode *pHead = *InstrMgr.plist;
	int index = 0;

	while (pHead != NULL)
	{
		InstrumentListNode *pNode = pHead;
		if (index == ringIdx)
		{
			Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Admesy);
			pMeter->pInstr = pNode->pInstr;
			if (Instrument_Type_USB == pNode->pInstr->type)
			{
				if (-1 == pNode->pInstr->Open(pNode->pInstr))
				{
					LOG_ERROR("Error open %s", pNode->pInstr->address);
				}
				else
				{
					pNode->pInstr->QueryID(pNode->pInstr);
					LOG_INFO("Init one instrument is %s, id %s", pNode->pInstr->address, pNode->pInstr->identifier);
				}
			}
			updateLED(panel);
			updateStrings(panel);

			return 0;
		}
		++index;
		pHead = pNode->next;
	}
	return -1;
}

int CVICALLBACK OnOkBtn(int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
	{

		Setting *pPicoSet = SetMgr.FindWithInstrFlag(Instrument_Picoammeter);
		Setting *pWaveSet = SetMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
		Setting *pLCRSet = SetMgr.FindWithInstrFlag(Instrument_LCRMeter);

		GetCtrlVal(panel, PANEL_CHECKBOX_LCR_SRC, &pLCRSet->isSignal);
		GetCtrlVal(panel, PANEL_CHECKBOX_WAVE_SRC, &pWaveSet->isSignal);
		GetCtrlVal(panel, PANEL_CHECKBOX_PICO_SRC, &pPicoSet->isSignal);
		GetCtrlVal(panel, PANEL_CHECKBOX_PICO_DATA, &pPicoSet->isColector);
		GetCtrlVal(panel, PANEL_CHECKBOX_LCR_DATA, &pLCRSet->isColector);

		if (pPicoSet->isSignal)
		{
			UI.ShowLCGraph(0);
		}
		else if (pLCRSet->isSignal)
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
	if (NULL != pMeter->pInstr)
	{
		ResetTextBox(panel, PANEL_TEXTBOX_PICO, pMeter->pInstr->identifier);
	}
	else
	{
		ResetTextBox(panel, PANEL_TEXTBOX_PICO, "");
	}

	pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
	if (NULL != pMeter->pInstr)
	{
		ResetTextBox(panel, PANEL_TEXTBOX_LCR, pMeter->pInstr->identifier);
	}
	else
	{
		ResetTextBox(panel, PANEL_TEXTBOX_LCR, "");
	}

	pMeter = DevMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
	if (NULL != pMeter->pInstr)
	{
		ResetTextBox(panel, PANEL_TEXTBOX_WAVE, pMeter->pInstr->identifier);
	}
	else
	{
		ResetTextBox(panel, PANEL_TEXTBOX_WAVE, "");
	}

	pMeter = DevMgr.FindWithInstrFlag(Instrument_Admesy);
	if (NULL != pMeter->pInstr)
	{
		ResetTextBox(panel, PANEL_TEXTBOX_ADMESY, pMeter->pInstr->identifier);
	}
	else
	{
		ResetTextBox(panel, PANEL_TEXTBOX_ADMESY, "");
	}
	return 0;
}

int updateLED(int panel)
{
	Device *pMeter = DevMgr.FindWithInstrFlag(Instrument_Picoammeter);
	if (NULL != pMeter->pInstr && pMeter->pInstr->status >= Instrument_Status_Connected)
	{
		SetCtrlVal(panel, PANEL_LED_PICO, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_PICO, 0);
	}
	pMeter = DevMgr.FindWithInstrFlag(Instrument_LCRMeter);
	if (NULL != pMeter->pInstr && pMeter->pInstr->status >= Instrument_Status_Connected)
	{
		SetCtrlVal(panel, PANEL_LED_LCR, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_LCR, 0);
	}
	pMeter = DevMgr.FindWithInstrFlag(Instrument_WaveformGenerator);
	if (NULL != pMeter->pInstr && pMeter->pInstr->status >= Instrument_Status_Connected)
	{
		SetCtrlVal(panel, PANEL_LED_WAVE, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_WAVE, 0);
	}
	pMeter = DevMgr.FindWithInstrFlag(Instrument_Admesy);
	if (NULL != pMeter->pInstr && pMeter->pInstr->status >= Instrument_Status_Connected)
	{
		SetCtrlVal(panel, PANEL_LED_ADMESY, 1);
	}
	else
	{
		SetCtrlVal(panel, PANEL_LED_ADMESY, 0);
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

		ClearListCtrl(panel, PANEL_RING_PICO);
		ClearListCtrl(panel, PANEL_RING_LCR);
		ClearListCtrl(panel, PANEL_RING_WAVE);
		ClearListCtrl(panel, PANEL_RING_ADMESY);

		//	SetCtrlIndex (panel, PANEL_RING_PICO, 2); // Based on index
		InstrumentListNode *pHead = *InstrMgr.plist;
		int index = 0;
		int count = 1;

		InsertListItem(panel, PANEL_RING_PICO, index, "None", count);
		InsertListItem(panel, PANEL_RING_LCR, index, "None", count);
		InsertListItem(panel, PANEL_RING_WAVE, index, "None", count);
		InsertListItem(panel, PANEL_RING_ADMESY, index, "None", count);
		index = -1;
		++count;
		while (pHead != NULL)
		{
			InstrumentListNode *pNode = pHead;

			InsertListItem(panel, PANEL_RING_PICO, index, pNode->pInstr->address, count);
			InsertListItem(panel, PANEL_RING_LCR, index, pNode->pInstr->address, count);
			InsertListItem(panel, PANEL_RING_WAVE, index, pNode->pInstr->address, count);
			InsertListItem(panel, PANEL_RING_ADMESY, index, pNode->pInstr->address, count);

			++count;
			pHead = pNode->next;
		}

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

int CVICALLBACK OnRefreshBtn(int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	case EVENT_COMMIT:
		InstrMgr.Scan(0);

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
		ConnectPico(panel);
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
		ConnectLCR(panel);
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
		ConnectWave(panel);
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
		ConnectAdmesy(panel);
		break;
	}
	return 0;
}
