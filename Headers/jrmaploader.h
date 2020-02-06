#pragma once

#include<math.h>
#include<stdio.h>
#include<gl/freeglut.h>

#include"../Headers/jrtexteditor.h"
#include"../Headers/jrmathlib.h"
#include"../Headers/jrbitmapimageloader.h"
#include"../Headers/jrms3dmodelloader.h"
#include"../Headers/jrms3dmodelrenderer.h"

#pragma comment(lib,"glut32.lib")

#using<mscorlib.dll>
using namespace System;

class CMapLoader : public CMS3DModelLoader
{
private:

	int				MAP_Z;
	int				MAP_X;
	int				MAP_SCALE;

	MSfloat			*map_height;

public:

	CMapLoader(int mapScale);
	~CMapLoader();

	bool		InitMap(char* filename);
	void		LoadMap();

	int			GetMapX();
	int			GetMapZ();
	int			GetMapScale();
	
	MSfloat*	GetMapHeightArray();
};
