#pragma once

#include"../Headers/jrmaploader.h"

#using<mscorlib.dll>
using namespace System;

CMapLoader :: CMapLoader(int mapScale)
{
	MAP_SCALE			=	mapScale;
}

CMapLoader :: ~CMapLoader()
{
}

bool CMapLoader :: InitMap(char* filename)
{
	if(InitModel(filename))
	{
		MAP_Z		=	sqrtl(numVertices);
		MAP_X		=	MAP_Z;

		map_height			=	new	MSfloat[MAP_Z];
		for(int i = 0; i < MAP_Z; i++)
		{
			map_height[i]	=	new	GLfloat[MAP_X];
		}

		return true;
	}

	return false;
}

void CMapLoader :: LoadMap()
{
	LoadModel();

	GLfloat	min		=	100000;
	GLfloat max		=	-100000;
	for(int i = 0; i < MAP_Z; i++)
	{
		for(int j = 0; j < MAP_X; j++)
		{
			vertices_array[(i * MAP_X + j) * 3]			*=	MAP_SCALE;
			
			if((vertices_array[(i * MAP_X + j) * 3 + 1]		*=	MAP_SCALE) < min)
			{
				min		=	vertices_array[(i * MAP_X + j) * 3 + 1];
			}
			if(vertices_array[(i * MAP_X + j) * 3 + 1] > max)
			{
				max		=	vertices_array[(i * MAP_X + j) * 3 + 1];
			}

			vertices_array[(i * MAP_X + j) * 3 + 2]		*=	MAP_SCALE;
		}
	}

	GLfloat	difference	=	(max		-	min) / 4;	

	for(int i = 0; i < MAP_Z; i++)
	{
		for(int j = 0; j < MAP_X; j++)
		{
			vertices_array[(i * MAP_X + j) * 3 + 1]		-=	difference;
		}
	}

	for(int i = 0; i < MAP_Z; i++)
	{
		for(int j = 0; j < MAP_X; j++)
		{
			map_height[i][j]	=	vertices_array[(i * MAP_X + j) * 3 + 1];
		}
	}

	for(int	i = 0; i < MAP_Z; i++)
	{
		for(int j = 0; j < MAP_X; j++)
		{
			if(j % 2 ==	0)
			{
				tex_coord_array[(i * MAP_X + j) * 2]		=	0.01;
			}
			else
			{
				tex_coord_array[(i * MAP_X + j) * 2]		=	0.99;
			}

			if(i % 2 == 0)
			{
				tex_coord_array[(i * MAP_X + j) * 2 + 1]	=	0.01;
			}
			else
			{
				tex_coord_array[(i * MAP_X + j) * 2 + 1]	=	0.99;
			}
		}
	}

	//MessageBoxA(NULL,CString::NumberToChar(map_height[250][250]/10),"s",MB_OK);
}

int	CMapLoader :: GetMapX()
{
	return	MAP_X;
}

int	CMapLoader :: GetMapZ()
{
	return	MAP_Z;
}

int	CMapLoader :: GetMapScale()
{
	return	MAP_SCALE;
}

MSfloat* CMapLoader :: GetMapHeightArray()
{
	return	map_height;
}