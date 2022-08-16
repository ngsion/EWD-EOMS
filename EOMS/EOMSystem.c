//==============================================================================
//
// Title:		EOMSystem.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 11:22:05 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "EOMSystem.h"
 

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static FILE * fp = NULL;

//==============================================================================
// Global functions
void setupLogger()
{  
	time_t now;//time_t
	time(&now);  
    
	struct tm *tblock;
    tblock = localtime(&now);
	
	char buf[64]={0};
    strftime(buf, 64, "log/EOMSlog_%Y%m%d_%H%M%S.txt", tblock);
  

    
	fp = fopen(buf,"a+");
	if	(NULL != fp)
	{
		 int result = log_add_fp(fp,LOG_DEBUG);
		 if	(result < 0)
		 {
			 log_fatal("log_add_fp failed");  
		 }
	}
	else
	{
		perror("error fopen");
	}
	//log_set_quiet(true);	
}


//==============================================================================
// Static functions
static int sInit(int x)
{
	 setupLogger();
	 return 0;
}
static int sShutdown(int x)
{
     if(NULL != fp)
	  {
		fclose(fp);
	  }
	  return 0;
}

//==============================================================================
// Global variables
EOMSystem System = {
	.Init = sInit,
	.Shutdown = sShutdown
	
};


