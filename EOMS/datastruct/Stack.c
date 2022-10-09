//==============================================================================
//
// Title:		Stack.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-09 at 20:18:22 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "Stack.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static bool InStack(struct Stack *pq, StackDataType data)
{
    if  (++pq->top < STACK_LENGTH)
    {
        pq->data[pq->top] = data;
        return true;
    }
    return false;
}
static StackDataType OutStack(struct Stack *pq)
{
    if(pq->top != pq->bottom)
    {
        StackDataType data = pq->data[pq->top--];
        return data;

    }
    return -1;
}
static unsigned int Size(struct  Stack * pq)
{
    return pq->top;
}
static void PrintStack(struct Stack * pq)
{
      while(pq->top != pq->bottom)
      {
        printf("[%d]: %f\n",pq->top,OutStack(pq));
      }
}
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
Stack *StackAllocInit()
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->bottom = 0;
    p->top = 0;
    p->OutStack = OutStack;
    p->InStack = InStack;
    p->PrintStack = PrintStack;
    p->Size = Size;
    return p;
}
void StackDelloc(Stack *pStack)
{
    if (NULL != pStack)
    {
        free(pStack);
        pStack = NULL;
    }
}

void TestStack()
{
    Stack * p = StackAllocInit();
    p->InStack(p,0.1);
    p->InStack(p,0.2);
    p->InStack(p,0.3);
    p->PrintStack(p);
    StackDelloc(p);
    
}
