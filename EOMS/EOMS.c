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
#include "logger/log.h"

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
void setupLogger()
{
	FILE * fp = fopen("EOMS-log.txt","a");
	if	(NULL != fp)
	{
		 int result = log_add_fp(fp,LOG_DEBUG);
		 if	(result < 0)
		 {
			 log_fatal("log_add_fp failed");  
		 }
	}
	//log_set_quiet(true);	
}

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	setupLogger();
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "EOMS.uir", PANEL));
	
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}

int CVICALLBACK onOKBtb (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			   log_trace("Hello %s", "world");
			   log_info("Hello %s", "world"); 
			break;
	}
	return 0;
}


