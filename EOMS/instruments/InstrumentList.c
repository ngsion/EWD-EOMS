//==============================================================================
//
// Title:		InstrumentList.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-17 at 11:45:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "InstrumentList.h"

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
void InstrumentListAllocInit(InstrumentListNode ** plist,Instrument * pInstr)
{
	*plist = (InstrumentListNode*) malloc(sizeof(InstrumentListNode));
	(*plist)->pInstr = pInstr;
	(*plist)->next = NULL;
}

void InstrumentListPushBack(InstrumentListNode ** plist, Instrument * pInstr)
{
	if (NULL == *plist)
	{
		InstrumentListAllocInit(plist,pInstr);
	}
	else
	{
		InstrumentListNode * ptr = *plist;
		while(ptr->next){
			ptr = ptr->next;
		}
		InstrumentListAllocInit(&(ptr->next),pInstr);
	}
	
}

void InstrumentListDelloc(InstrumentListNode ** plist)
{
	InstrumentListNode * cur = *plist;
	InstrumentListNode * next = NULL;
	while (NULL != cur)
	{
		next = cur->next;
		InstrumentDelloc(cur->pInstr);
		free(cur);
		cur = next;
	}
	*plist = NULL;
}
