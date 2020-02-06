#pragma once

#include"../Headers/jrobject.h"

CObject :: CObject(CMS3DModelLoader *ldr, CMS3DModelRenderer *rnd)
{
	model_loader		=	ldr;
	model_renderer		=	rnd;
	number				=	counter++;

	ClearObject();
}

CObject :: ~CObject()
{
	delete[] model_loader;
	delete[] model_renderer;
	counter--;
}

int CObject :: counter	=	0;

void CObject :: ClearObject()
{
	position.x	=	0.0;
	position.y	=	0.0;
	position.z	=	0.0;

	rotation.x	=	0.0;
	rotation.y	=	0.0;
	rotation.z	=	0.0;

	center.x	=	0.0;
	center.y	=	0.0;
	center.z	=	0.0;

	radius.x	=	0.0;
	radius.y	=	0.0;
	radius.z	=	0.0;

	min.x	=	99999;
	min.y	=	99999;
	min.z	=	99999;

	max.x	=	-99999;
	max.y	=	-99999;
	max.z	=	-99999;

}

void CObject :: InitObject()
{
	//SetCenterAndRadius();
	SetMinMax();
	SetCubeBound();
	SetTextPosition();
}

void CObject :: SetMinMax()
{
	GLfloat	*vertex		=	model_loader->GetVerticesArray();

	for(int i = 0; i < model_loader->GetNumberOfVertex(); i++)
	{
		if(vertex[i * 3] < min.x)
		{
			min.x	=	vertex[i * 3];
		}

		if(vertex[i * 3 + 1] < min.y)
		{
			min.y	=	vertex[i * 3 + 1];
		}

		if(vertex[i * 3 + 2] < min.z)
		{
			min.z	=	vertex[i * 3 + 1];
		}

		if(vertex[i * 3] > max.x)
		{
			max.x	=	vertex[i * 3];
		}

		if(vertex[i * 3 + 1] > max.y)
		{
			max.y	=	vertex[i * 3 + 1];
		}

		if(vertex[i * 3 + 2] > max.z)
		{
			max.z	=	vertex[i * 3 + 1];
		}
	}
/*
	center.x	=	(float)((max.x	+	min.x)	/	2.0f);
	center.y	=	(float)((max.y	+	min.y)	/	2.0f);
	center.z	=	(float)((max.z	+	min.z)	/	2.0f);

	radius.x	=	max.x	-	center.x;
	radius.y	=	max.y	-	center.y;
	radius.z	=	max.z	-	center.z;

	radius.x	=	abs(radius.x);
	radius.y	=	abs(radius.y);
	radius.z	=	abs(radius.z);*/
	/*
	{
		String ^str;
		str = loader->GetNumberOfTotalFrame().ToString();
		char *ch=new char[str->Length];
		for(int i=0;i<str->Length;i++)
			ch[i]=str[i];
		MessageBoxA(NULL,ch,"radius.x",MB_OK);
	}
	*/
}

void CObject :: SetCubeBound()
{
	cube_bound.center.x				=	(float)((max.x	+	min.x)	/	2.0f);
	cube_bound.center.y				=	(float)((max.y	+	min.y)	/	2.0f);
	cube_bound.center.z				=	(float)((max.z	+	min.z)	/	2.0f);

	cube_bound.magnitudeOf3Axis.x	=	max.x	-	min.x;
	cube_bound.magnitudeOf3Axis.y	=	max.y	-	min.y;
	cube_bound.magnitudeOf3Axis.z	=	max.z	-	min.z;

	cube_bound.n1.x					=	min.x;
	cube_bound.n1.y					=	min.y;
	cube_bound.n1.z					=	max.z;

	cube_bound.n2.x					=	max.x;
	cube_bound.n2.y					=	min.y;
	cube_bound.n2.z					=	max.z;

	cube_bound.n3.x					=	max.x;
	cube_bound.n3.y					=	max.y;
	cube_bound.n3.z					=	max.z;

	cube_bound.n4.x					=	min.x;
	cube_bound.n4.y					=	max.y;
	cube_bound.n4.z					=	max.z;

	cube_bound.f1.x					=	min.x;
	cube_bound.f1.y					=	min.y;
	cube_bound.f1.z					=	min.z;

	cube_bound.f2.x					=	max.x;
	cube_bound.f2.y					=	min.y;
	cube_bound.f2.z					=	min.z;

	cube_bound.f3.x					=	max.x;
	cube_bound.f3.y					=	max.y;
	cube_bound.f3.z					=	min.z;

	cube_bound.f4.x					=	min.x;
	cube_bound.f4.y					=	max.y;
	cube_bound.f4.z					=	min.z;

	//cube_bound.magnitudeOfDiagonal	=	
}

void CObject :: SetTextPosition()
{
	text_one.x	=	min.x;
	text_one.y	=	max.y	+	1.0;
	text_one.z	=	center.z;

	text_two.x	=	min.x;
	text_two.y	=	max.y	+	2.0;
	text_two.z	=	center.z;

	text_three.x	=	min.x;
	text_three.y	=	max.y	+	3.0;
	text_three.z	=	center.z;

}

void CObject :: SetPosition(vec3 p)
{
	position		=	p;
	text_one		=	p;
	text_two		=	p;
	text_three		=	p;

	text_one.y		=	max.y	+	1.0;
	text_two.y		=	max.y	+	2.0;
	text_three.y	=	max.y	+	3.0;

}

void CObject :: SetPosition(vec_t x, vec_t y, vec_t z)
{
	position.x		=	x;
	position.y		=	y;
	position.z		=	z;

	text_one.x		=	x;
	text_one.z		=	z;

	text_two.x		=	x;
	text_two.z		=	z;

	text_three.x		=	x;
	text_three.z		=	z;
}

void CObject :: SetHeight(GLfloat h)
{
	position.y	=	h;
}

void CObject :: SetRotation(vec3 r)
{
	position	=	r;
}

void CObject :: SetRotation(vec_t x, vec_t y, vec_t z)
{
	rotation.x	=	x;
	rotation.y	=	y;
	rotation.z	=	z;
}

void CObject :: SetRotationAroundXAxis(GLfloat	r)
{
	rotation.x	=	r;
}

void CObject :: SetRotationAroundZAxis(GLfloat	r)
{
	rotation.z	=	r;
}

void CObject :: OnDraw()
{

	model_renderer->DrawModel(position,rotation);

}

vec3 CObject :: GetPosition() const
{
	return position;
}

vec3 CObject :: GetRotation() const
{
	return rotation;
}

vec3 CObject :: GetRadius() const
{
	return radius;
}

vec3 CObject :: GetCenter() const
{
	return center;
}

int CObject :: GetCounter()
{
	return counter;
}