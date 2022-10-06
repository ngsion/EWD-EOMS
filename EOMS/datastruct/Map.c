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
static int SetMap(Map *map, char *key, int value)
{
	int index = 0;
	bool added = false;

	for (index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key && 0 == strcmp(map->array[index].key, key))
		{
			map->array[index].value = value;
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
				map->array[index].value = value;
				added = true;
				break;
			}
		}
	}

	if (false == added)
		return 0;
	return -1;
}

static int GetValue(Map *map, char *key)
{
	int value = -1;
	for (int index = 0; index < MAP_NODE_LENGTH; index++)
	{
		if (NULL != map->array[index].key && 0 == strcmp(map->array[index].key, key))
		{
			value = map->array[index].value;
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
			printf("[%d]: %s -> %d\n", index, map->array[index].key, map->array[index].value);
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
		map->array[index].value = 0;
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
		map->SetMap(map,"hello",2);
		map->SetMap(map,"abc",3);
		map->SetMap(map,"a",3);
		map->PrintMap(map);
		map->RemoveKey(map,"a");
		map->PrintMap(map);
		printf("get value %d",map->GetValue(map,"ab"));
		map->SetMap(map,"abc",8);
		map->PrintMap(map);   
		MapDelloc(map);
	}
	
}
