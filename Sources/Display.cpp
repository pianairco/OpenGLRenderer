#pragma once

#include<gl/glaux.h>
#include<gl/freeglut.h>
#include<gl/glext.h>
#include<stdlib.h>
#include<math.h>
#include <Mmsystem.h>
#include<time.h>

#include"../Headers/jrms3dmodelloader.h"
#include"../Headers/jrms3dmodelrenderer.h"
#include"../Headers/jrobject.h"
#include"../Headers/jrmovementobject.h"
#include"../Headers/jrtexteditor.h"
#include"../Headers/jrmaploader.h"
#include"../Headers/jrmaprenderer.h"
#include"../Headers/jrmapgame.h"
#include"../Headers/jrgamelogic.h"

#using<mscorlib.dll>
using namespace System;

#pragma comment(lib,"glaux.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"Winmm.lib")

//#define BITMAP_ID 0x4D42
//#define PI 3.14159 // the constant value for PI

#define		OBJECT_NUMBER	10

//_______________________________________________________________________________

CMovementObject		*model_object;

//_______________________________________________________________________________

CMovementObject		*sky_object;

//_______________________________________________________________________________


CMapGame			*map;

//_______________________________________________________________________________

CGameLogic			*game_logic;

//--------- Mouse/Camera Variables

extern Int32 width,height;

//------------

int SetupRC()
{
	CString::InitClass();

	CMapLoader	*map_loader		=	new CMapLoader(50);
	if(map_loader->InitMap("map.ms3d"))
	{
		map_loader->LoadMap();
	}
	CMapRenderer	*map_renderer	=	new	CMapRenderer(map_loader);

	map		=	new CMapGame(map_loader,map_renderer);
	map->InitMapGame();

//----------------------------------------------------------

	CMS3DModelLoader	*sky_loader			=	new CMS3DModelLoader();
	CMS3DModelRenderer	*sky_renderer		=	new CMS3DModelRenderer(sky_loader);

	
	if(sky_loader->InitModel("sky.ms3d"))
	{	
		sky_loader->LoadModel();	
	}

	sky_object		=	new CMovementObject(sky_loader,sky_renderer,1);
	sky_object->InitObject();
	sky_object->SetupAnimationFPS(0,1);
	sky_object->SetPosition(0,-100,100);
	sky_object->SetRotation(0.0,0.0,0.0);

//------------------------------------------------------------

	CMS3DModelLoader	*model_loader		=	new CMS3DModelLoader();
	CMS3DModelRenderer	*model_renderer		=	new CMS3DModelRenderer(model_loader);


	if(model_loader->InitModel("dwarf2.ms3d"))
	{	

		model_loader->LoadModel();	
	}

	model_object	=	new CMovementObject(model_loader,model_renderer,3);
	model_object->InitObject();

	model_object->SetPosition(2, 0, 0);
	model_object->SetRotation(0.0, Q_PI, 0.0);

	model_object->SetupAnimState(1,200);
	model_object->SetupAnimationFPS(1,20);
		
	model_object->SetupAnimState(1,200);
	model_object->SetState(1);

//-------------------------------------------------------------
		
	game_logic		=	new	CGameLogic(map,model_object);
	

//	MessageBoxA(NULL,CString::NumberToChar(m_object[0]->GetCounter()),"counter",MB_OK);

	glClearColor(0.4f,0.3f,0.8f,0.0f);
	glColor3f(1,1,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE_MODE);
	glFrontFace(GL_CCW);

	glShadeModel(GL_SMOOTH);

	return TRUE;
}

GLvoid ReSizeGLScene(INT32 width,INT32 height)
{
	if(height==0)
	{
		height=1;
	}
	glViewport(0,0,width,height);

	float aspect=(GLfloat)width/(GLfloat)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45,(GLfloat)width/(GLfloat)height,1,100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ShowAxis();


int DisplayFunc(INT32 width,INT32 height)
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	map->OnDraw();
	model_object->OnAnimate();

/*	game_logic->OnMove();
	game_logic->OnDraw();
	sky_object->OnAnimate();
*/
	ShowAxis();	

	glFlush();
	return TRUE;
}

void ShowAxis()
{
	glLineWidth(2);
	glBegin(GL_LINES);
	
	//----------------x
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(100000,0,0);

	glColor3f(0.3,0,0);
	glVertex3f(0,0,0);
	glVertex3f(-100000,0,0);

	//----------------y

	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1000,0);

	glColor3f(0,0.3,0);
	glVertex3f(0,0,0);
	glVertex3f(0,-1000,0);

	//-----------------z

	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,100000);

	glColor3f(0,0,0.3);
	glVertex3f(0,0,0);
	glVertex3f(0,0,-100000);

	glEnd();

}

