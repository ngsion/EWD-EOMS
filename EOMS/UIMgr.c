#include <cvirte.h>
#include <userint.h>
#include "Entry.h"

static int panelHandle;

//==============================================================================
//
// Title:		UIMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-09 at 21:50:02 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "UIMgr.h"
#include "EOMSystem.h"


//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int panelHandle = 0;
static int status = -1;
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
static int ShowEntry(int x)
{
	if (-1 != status)
	{
		QuitUserInterface(0);
		DiscardPanel(panelHandle);
	}

	panelHandle = LoadPanel(0, "Entry.uir", PANEL);
	DisplayPanel(panelHandle);
	status = RunUserInterface();

	return 0;
}
static int ShowLCGraph(int x)
{
	QuitUserInterface(0);
	DiscardPanel(panelHandle);
	
	panelHandle = LoadPanel(0, "LCGraph.uir", PANEL);
	/* display the panel and run the user interface */
	DisplayPanel(panelHandle);
	status = RunUserInterface();

	return 0;
}
static int ShowCVGraph(int x)
{
	QuitUserInterface(0);
	DiscardPanel(panelHandle);
	
	panelHandle = LoadPanel(0, "CVGraph.uir", PANEL);
	/* display the panel and run the user interface */
	DisplayPanel(panelHandle);
	status = RunUserInterface();

	return 0;
}
static int ShowGraph(int x)
{
	QuitUserInterface(0);
	DiscardPanel(panelHandle);
	
	panelHandle = LoadPanel(0, "EOMS.uir", PANEL);
	/* display the panel and run the user interface */
	DisplayPanel(panelHandle);
	status = RunUserInterface();

	return 0;
}
//==============================================================================
// Global variables
UIMgr UI = {
	.ShowEntry = ShowEntry,
	.ShowGraph = ShowGraph,
	.ShowLCGraph = ShowLCGraph,
	.ShowCVGraph = ShowCVGraph 
	};

int main(int argc, char *argv[])
{
	if (InitCVIRTE(0, argv, 0) == 0)
		return -1; /* out of memory */
	System.Init(0);
	UI.ShowEntry(0);
	System.Shutdown(0);
	return 0;
}
