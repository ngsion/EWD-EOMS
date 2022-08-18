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
InstrumentListNode * CreateInstrumentListNode(Instrument * pInstr)
{
	InstrumentListNode *newNode = (InstrumentListNode*) malloc(sizeof(InstrumentListNode));
	newNode->pInstr = pInstr;
	newNode->next = NULL;
	return newNode;
}

void InstrumentListPushBack(InstrumentListNode ** pList, Instrument * pInstr)
{
	if (NULL == *pList)
	{
		*pList = CreateInstrumentListNode(pInstr);
	}
	else
	{
		InstrumentListNode * tail = *pList;
		while(tail->next){
			tail = tail->next;
		}
		tail->next = CreateInstrumentListNode(pInstr);
	}
	
}

void InstrumentListClear(InstrumentListNode ** pList)
{
	InstrumentListNode * cur = *pList;
	InstrumentListNode * next = NULL;
	while (NULL != cur)
	{
		next = cur->next;
		InstrumentDelloc(cur->pInstr);
		free(cur);
		cur = next;
	}
	*pList = NULL;
}
