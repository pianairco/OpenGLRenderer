#pragma once

#include<math.h>
#include<stdio.h>
#include<gl/freeglut.h>

#include"../Headers/jrtexteditor.h"
#include"../Headers/jrmaploader.h"
#include"../Headers/jrmaprenderer.h"

#pragma comment(lib,"glut32.lib")

#using<mscorlib.dll>
using namespace System;

class CMapGame
{
private:

	CMapLoader					*map_loader;
	CMapRenderer				*map_renderer;

	MSfloat						*map_height;
	
	int							MID_CELL;
	int							MAP_X;
	int							MAP_Z;
	int							MAP_SCALE;

public:

	CMapGame(CMapLoader *ldr, CMapRenderer *rnd);
	~CMapGame();

	void InitMapGame();
	
	int		GetMapX();
	int		GetMapZ();
	int		GetMapScale();
	int		GetMidCell();
	
	GLfloat		GetHeight(int z, int x);

	void OnDraw();
};