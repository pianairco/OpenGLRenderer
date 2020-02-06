#pragma once

#include"../Headers/jrmaploader.h"

class CMapRenderer 
{
private:

	CMapLoader	*map_loader;

public:

	CMapRenderer(CMapLoader *ldr);
	~CMapRenderer();

	void BindMaterial(int materialIndex);
	void TearMaterial();

	void DrawMap();

};