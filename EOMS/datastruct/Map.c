//==============================================================================
//
// Title:		Map.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-06 at 14:30:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "Map.h"
#include <stdbool.h> 

//==============================================================================
// Constants
#if !HAVE_STRDUP
#undef strdup
char * strdup(const char *s)
{
	size_t len = strlen(s) + 1;
	void * newStr = malloc(len);
	return (NULL == newStr ?  NULL : (char*)memcpy(newStr,s,len)); 
}
#endif
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

static int SetMap(Map *map, char *key, unsigned int cvalue, unsigned int rvalue)
{
	int index = 0;
	bool added = false;

	for (index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key && 0 == strcmp(map->array[index].key, key))
		{
			map->array[index].cvalue = cvalue;
			map->array[index].rvalue = rvalue;
			added = true;
			break;
		}
	}

	if (false == added)
	{
		for (index = 0; index < MAP_NODE_LENGTH; index++)
		{
			if (NULL == map->array[index].key)
			{
				map->array[index].key = strdup(key);
				map->array[index].cvalue = cvalue;
			    map->array[index].rvalue = rvalue;
				added = true;
				break;
			}
		}
	}

	if (false == added)
		return 0;
	return -1;
}

static int GetValue(Map *map, char *key, unsigned int * cvalue, unsigned int * rvalue)
{
	int value = -1;
	for (int index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key && 0 == strcmp(map->array[index].key, key))
		{
			*cvalue = map->array[index].cvalue;
			*rvalue = map->array[index].rvalue;
			value = 0;
			break;
		}
	}
	return value;
}

int RemoveKey(Map *map, char *key)
{
	for (int index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key && 0 == strcmp(map->array[index].key, key))
		{
			free(map->array[index].key);
			map->array[index].key = NULL;
			return 0;
		}
	}
	return -1;
}

static void PrintMap(Map *map)
{
	for (int index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key)
		{
			printf("[%d]: %s -> %d , %d\n", index, map->array[index].key, map->array[index].cvalue, map->array[index].rvalue);
		}
	}
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
Map *MapAllocInit()
{
	Map *map = (Map *)malloc(sizeof(Map));
	map->SetMap = SetMap;
	map->GetValue = GetValue;
	map->PrintMap = PrintMap;
	map->RemoveKey =  RemoveKey;
	for (int index = 0; index < MAP_NODE_LENGTH; index++)
	{
		map->array[index].key = NULL;
		map->array[index].cvalue = 0;
		map->array[index].rvalue = 0;
	}
	return map;
}
void MapDelloc(Map *map)
{
	if (NULL != map)
	{
		for (int index = 0; index < MAP_NODE_LENGTH; index++)
		{
			if (NULL != map->array[index].key)
			{
				free(map->array[index].key);
				map->array[index].key = NULL;
			}
		}
		free(map);
		map = NULL;
	}
}

void TestMap()
{
	Map * map = MapAllocInit();
	if (map)
	{
		map->SetMap(map,"hello",2,2);
		map->SetMap(map,"abc",3,4);
		map->SetMap(map,"a",3,4);
		map->PrintMap(map);
		map->RemoveKey(map,"a");
		map->PrintMap(map);
		unsigned int column = 0;
		unsigned int row = 0;
		printf("get value %d",map->GetValue(map,"ab",column,row));
		map->SetMap(map,"abc",8,5);
		map->PrintMap(map);   
		MapDelloc(map);
	}
	
}
