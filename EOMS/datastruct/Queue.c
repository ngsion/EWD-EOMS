//==============================================================================
//
// Title:		Queue.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-09-26 at 9:54:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "Queue.h"
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static bool Push(Queue *pq, QDataType data)
{
	if (NULL != pq)
	{
		QNode *newNode = (QNode *)malloc(sizeof(QNode));
		if (NULL != newNode)
		{
			newNode->data = data;
			newNode->next = NULL;

			if (NULL == pq->tail)
			{
				pq->head = pq->tail = newNode;
			}
			else
			{
				pq->tail->next = newNode;
				pq->tail = newNode;
			}
			++pq->size;
			return true;
		}
	}
	return false;
}
static bool Pop(Queue *pq, QDataType *data)
{
	if (NULL != pq && NULL != data)
	{
		if (NULL != pq->head)
		{
			if (NULL == pq->head->next)
			{
				*data = pq->head->data;
				--pq->size;
				free(pq->head);
				pq->head = pq->tail = NULL;
			}
			else
			{
				*data = pq->head->data;
				--pq->size;
				QNode *next = pq->head->next;
				free(pq->head);
				pq->head = next;
			}

			return true;
		}
	}
	return false;
}
static bool Empty(Queue *pq)
{
	if (NULL != pq)
	{
		return NULL == pq->head;
	}
	return false;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
Queue *QueueAllocInit()
{
	Queue *pq = (Queue *)malloc(sizeof(Queue));
	if (NULL == pq)
	{
		LOG_FATAL("Error creating an Queue.");
	}
	else
	{
		pq->head = NULL;
		pq->tail = NULL;
		pq->size = 0;
		pq->Empty = Empty;
		pq->Pop = Pop;
		pq->Push = Push;
	}
	return pq;
}

void QueueDelloc(Queue *pq)
{
	if (NULL != pq)
	{
		QNode *cur = pq->head;
		while (cur)
		{
			QNode *next = cur->next;
			free(cur);
			cur = next;
		}

		free(pq);
		pq = NULL;
	}
}

void TestQueue()
{
	Queue *qu = QueueAllocInit();
	qu->Push(qu, 0.4);
	qu->Push(qu, 0.5);

	printf("queeu size %d", qu->size);
	double data;
	qu->Pop(qu, &data);
	printf("queeu size %d , data is %f", qu->size, data);
}
