#pragma once

#include"../Headers/jrmapgame.h"

CMapGame :: CMapGame(CMapLoader *ldr, CMapRenderer *rnd)
{
	map_loader		=	ldr;
	map_renderer	=	rnd;
}

CMapGame :: ~CMapGame()
{
	delete[]		map_loader;
	delete[]		map_renderer;
}

void CMapGame :: InitMapGame()
{
	MAP_X		=	map_loader->GetMapX();
	MAP_Z		=	map_loader->GetMapZ();
	MAP_SCALE	=	map_loader->GetMapScale();
	MID_CELL	=	(MAP_X	-	1)	/	2;
	map_height	=	map_loader->GetMapHeightArray();
}
	
int	CMapGame :: GetMapX()
{
	return MAP_X;
}

int	CMapGame :: GetMapZ()
{
	return MAP_Z;
}

int	CMapGame :: GetMapScale()
{
	return MAP_SCALE;
}

int	CMapGame :: GetMidCell()
{
	return MID_CELL;
}

GLfloat	CMapGame :: GetHeight(int z, int x)
{
	return	map_height[z][x];
}

void CMapGame :: OnDraw()
{
	map_renderer->DrawMap();
}