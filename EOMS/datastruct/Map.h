//==============================================================================
//
// Title:		Map.h
// Purpose:		A short description of the interface.
//
// Created on:	2022-10-06 at 14:30:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Map_H__
#define __Map_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define MAP_NODE_LENGTH 100
//==============================================================================
// Types
typedef struct MapNode
{
    char * key;
    int value;
}MapNode;


typedef struct Map
{
    MapNode array[MAP_NODE_LENGTH]; 
    int (*SetMap)(struct Map * map, char * key, int value);
    int (*GetValue)(struct Map * map, char * key);
    int (*RemoveKey)(struct Map * map, char * key);
    void (*PrintMap)(struct Map * map);
}Map;

//==============================================================================
// External variables

//==============================================================================
// Global functions
Map *MapAllocInit();
void MapDelloc(Map *pMap);

void TestMap();

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Map_H__ */
