//==============================================================================
//
// Title:		Queue.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-09-26 at 9:54:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Queue_H__
#define __Queue_H__

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

    //==============================================================================
    // Types
    typedef double QDataType;
    typedef struct QueueNode
    {
        struct QueueNode *next;
        QDataType data;

    } QNode;
    typedef struct Queue
    {
        QNode *tail;
        QNode *head;
        int size;

        bool (*Push)(struct Queue* pq, QDataType data);
        bool (*Pop)(struct Queue* pq, QDataType * data);
        bool (*Empty)(struct Queue* pq);

    } Queue;

    //==============================================================================
    // External variables

    //==============================================================================
    // Global functions
    Queue *QueueAllocInit();
    void QueueDelloc(Queue *pQueue);

#ifdef __cplusplus
}
#endif

#endif /* ndef __Queue_H__ */
