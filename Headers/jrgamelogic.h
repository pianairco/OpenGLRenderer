#pragma once

#include"../Headers/jrobject.h"
#include"../Headers/jrmovementobject.h"
#include"../Headers/jrmapgame.h"
#include"../Headers/jrmathematicslibrary.h"

class CGameLogic
{
private:
	
	CMapGame			*map;
	CMovementObject		*model;
	vec3				t1,t2,t3;

public:

	CGameLogic(CMapGame *mg,CMovementObject	*mo);
	~CGameLogic();

	void SetHeightInPosition();
	void SetDirectionXZ();

	void OnMove();
	void OnDraw();

	void DrawTriangle();
};