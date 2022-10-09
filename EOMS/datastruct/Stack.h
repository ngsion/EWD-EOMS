//==============================================================================
//
// Title:		Stack.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-09 at 20:18:22 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Stack_H__
#define __Stack_H__

#ifdef __cplusplus
extern "C"
{
#endif

    //==============================================================================
    // Include files

#include "cvidef.h"
#include <stdbool.h> 

//==============================================================================
// Constants
#define STACK_LENGTH 100
    typedef double StackDataType;

    //==============================================================================
    // Types
    typedef struct Stack
    {
        StackDataType data[STACK_LENGTH];
        unsigned int top;
        unsigned int bottom;

        bool (*InStack)(struct Stack *pq, StackDataType data);
        StackDataType (*OutStack)(struct Stack *pq);
        void (*PrintStack)(struct Stack * pq);
        unsigned int (*Size)(struct  Stack * pq);

    } Stack;
    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    // Global functions
    Stack *StackAllocInit();
    void StackDelloc(Stack *pStack);

    void TestStack();

#ifdef __cplusplus
}
#endif

#endif /* ndef __Stack_H__ */
