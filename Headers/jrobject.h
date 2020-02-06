#pragma once

#include<gl/freeglut.h>

#include"../Headers/jrms3dmodelloader.h"
#include"../Headers/jrms3dmodelrenderer.h"
#include"../Headers/jrmathlib.h"

#pragma comment(lib,"glut32.lib")

#using<mscorlib.dll>
using namespace System;

struct ST_Cube_bound
{
	vec3	n1;
	vec3	n2;
	vec3	n3;
	vec3	n4;
	
	vec3	f1;
	vec3	f2;
	vec3	f3;
	vec3	f4;

	vec3	center;
	vec3	magnitudeOf3Axis;

	int		magnitudeOfDiagonal;
};

class CObject
{
protected:

	CMS3DModelLoader	*model_loader;
	CMS3DModelRenderer	*model_renderer;
	
	vec3		min;
	vec3		max;

	//------------------------------------------------

	ST_Cube_bound	cube_bound;

	//------------------------------------------------

	vec3		position;
	vec3		rotation;

	vec3		radius;
	vec3		center;

	static int counter;
	int			number;

	vec3		text_one;
	vec3		text_two;
	vec3		text_three;

public:

	CObject(CMS3DModelLoader *ldr,CMS3DModelRenderer *rnd);
	~CObject();

	void ClearObject();
	virtual void InitObject();
	void SetMinMax();
	void SetCubeBound();
	void SetTextPosition();

	void SetPosition(vec3 p);
	void SetPosition(vec_t x, vec_t y, vec_t z);
	void SetHeight(GLfloat h);

	void SetRotation(vec3 r);
	void SetRotation(vec_t x, vec_t y, vec_t z);
	void SetRotationAroundXAxis(GLfloat	r);
	void SetRotationAroundZAxis(GLfloat	r);

	void OnDraw();

	vec3 GetPosition() const;
	vec3 GetRotation() const;
	vec3 GetRadius() const;
	vec3 GetCenter() const;
	int static GetCounter();

};