#pragma once

#include"../Headers/jrgamelogic.h"

CGameLogic :: CGameLogic(CMapGame *mg,CMovementObject	*mo)
{
	map		=	mg;
	model	=	mo;
	model->SetMovementSpeed(0.2f);
	model->SetSpinSpeed(0.001f);
	//SetHeightInPosition();
	t1.x	=	0;t1.y	=	0;t1.z	=	0;
	t2.x	=	0;t2.y	=	0;t2.z	=	0;
	t3.x	=	0;t3.y	=	0;t3.z	=	0;
}

CGameLogic :: ~CGameLogic()
{
	delete[]	map;
	delete[]	model;
}
/*
void CGameLogic :: SetHeightInPosition()
{

	int		lx1,lz1,lx2,lz2;
	GLfloat x,z,x1,z1,x2,z2;

	lx1	=	model->GetPosition().x / map->GetMapScale()	+ map->GetMidCell();
	lz1	=	model->GetPosition().z / map->GetMapScale()	+ map->GetMidCell();

	lx2	=	lx1+1;
	lz2	=	lz1+1;
	
	x1	=	lx1 * map->GetMapScale();
	z1	=	lz1 * map->GetMapScale();

	x2	=	lx2 * map->GetMapScale();
	z2	=	lz2 * map->GetMapScale();

	x	=	model->GetPosition().x;
	z	=	model->GetPosition().z;

	GLfloat	len1,len2;
	len1	=	pow((x1-x),2);
	len2	=	pow((x2-x),2);

	if(len1>=len2)
	{
		model->SetHeight(map->GetHeight(lz1,lx1));
	}
	else
	{
		model->SetHeight(map->GetHeight(lz2,lx2));
	}

}
*/
void CGameLogic :: SetHeightInPosition()
{
	int		lx1,lz1,lx2,lz2;
	GLfloat x,z,x1,z1,x2,z2;

	lx1	=	model->GetPosition().x / map->GetMapScale()	+ map->GetMidCell();
	lz1	=	model->GetPosition().z / map->GetMapScale()	+ map->GetMidCell();

	lx2	=	lx1+1;
	lz2	=	lz1+1;
	
	x1	=	lx1 * map->GetMapScale();
	z1	=	lz1 * map->GetMapScale();

	x2	=	lx2 * map->GetMapScale();
	z2	=	lz2 * map->GetMapScale();

	x	=	model->GetPosition().x;
	z	=	model->GetPosition().z;

	GLfloat	len1,len2;
	len1	=	sqrt(pow((x1-x),2) + pow((z1-z),2));
	len2	=	sqrt(pow((x2-x),2) + pow((z2-z),2));

	GLfloat x3,z3,x4,z4;
	int	lx3,lz3,lx4,lz4;

	if(len1>=len2)
	{
		lx3		=	lx1 + 1;
		lz3		=	lz1;
		
		lx4		=	lx1;
		lz4		=	lz1 + 1;

		x3		=	lx3	*	map->GetMapScale();
		z3		=	lz3 *	map->GetMapScale();

		x4		=	lx4	*	map->GetMapScale();
		z4		=	lz4 *	map->GetMapScale();

		GLfloat	lenght1,lenght3,lenght4,lenght;
		lenght1	=	len1;
		lenght3	=	sqrt(pow((x3-x),2) + pow((z3-z),2));
		lenght4	=	sqrt(pow((x4-x),2) + pow((z4-z),2));

		lenght	=	lenght1 + lenght3 + lenght4;

		GLfloat	h1,h3,h4,height;

		h1		=	map->GetHeight(lz1,lx1);
		h3		=	map->GetHeight(lz3,lx3);
		h4		=	map->GetHeight(lz4,lx4);


		//height	=	((h1 * lenght1) + (h3 * lenght3) + (h4 * lenght4)) / lenght;
		//height	=	(h1 * (lenght1/lenght)) + (h3 * (lenght3/lenght)) + (h4 * (lenght4/lenght));
		
		//model->SetHeight(height);
		model->SetHeight(h1);
	}
	else
	{
		lx3		=	lx2 - 1;
		lz3		=	lz2;
		
		lx4		=	lx2;
		lz4		=	lz2 - 1;

		x3		=	lx3	*	map->GetMapScale();
		z3		=	lz3 *	map->GetMapScale();

		x4		=	lx4	*	map->GetMapScale();
		z4		=	lz4 *	map->GetMapScale();

		GLfloat	lenght2,lenght3,lenght4,lenght;
		lenght2	=	len2;
		lenght3	=	sqrt(pow((x3-x),2) + pow((z3-z),2));
		lenght4	=	sqrt(pow((x4-x),2) + pow((z4-z),2));

		lenght	=	lenght2 + lenght3 + lenght4;
		
		GLfloat	h2,h3,h4,height;

		h2		=	map->GetHeight(lz2,lx2);
		h3		=	map->GetHeight(lz3,lx3);
		h4		=	map->GetHeight(lz4,lx4);

		//height	=	((h2 * lenght2) + (h3 * lenght3) + (h4 * lenght4)) / lenght;
		//height	=	(h2 * (lenght2/lenght)) + (h3 * (lenght3/lenght)) + (h4 * (lenght4/lenght));

		//model->SetHeight(height);
		model->SetHeight(h2);
	}

}


void CGameLogic :: OnMove()
{
	model->GoForward();
	//SetDirectionXZ();
	//model->SpinRight();
	SetHeightInPosition();
}

void CGameLogic :: DrawTriangle()
{
	int		lx1,lz1;
	vec3	v1,v2,v3,v4,cp1,cp2;
	GLfloat	dp1,dp2;

	v1.x	=	lx1	*	map->GetMapScale();
	v1.y	=	map->GetHeight(lz1+map->GetMidCell(),lx1+map->GetMidCell());
	v1.z	=	lz1	*	map->GetMapScale();

	v2.x	=	(lx1 + 1)	*	map->GetMapScale();
	v2.y	=	map->GetHeight(lz1+map->GetMidCell(),(lx1 + map->GetMidCell() + 1));
	v2.z	=	lz1	*	map->GetMapScale();

	v3.x	=	(lx1 + 1)	*	map->GetMapScale();
	v3.y	=	map->GetHeight(lz1+map->GetMidCell()+1,lx1+map->GetMidCell()+1);
	v3.z	=	(lz1 + 1)	*	map->GetMapScale();

	v4.x	=	lx1	*	map->GetMapScale();
	v4.y	=	map->GetHeight(lz1+map->GetMidCell()+1,lx1+map->GetMidCell());
	v4.z	=	(lz1 + 1)	*	map->GetMapScale();

	cp1		=	CrossProductRespectToOther3D(v2,v4,v1);
	cp2		=	CrossProductRespectToOther3D(v2,v4,v3);

	dp1		=	DistanceBetweenVectors3D(model->GetCenter(),cp1);
	dp2		=	DistanceBetweenVectors3D(model->GetCenter(),cp2);

	lx1	=	model->GetPosition().x / map->GetMapScale()	;
	lz1	=	model->GetPosition().z / map->GetMapScale()	;

	if(dp1<=dp2)
	{
		t1.x	=	lx1	*	map->GetMapScale();
		t1.y	=	map->GetHeight(lz1+map->GetMidCell(),lx1+map->GetMidCell());
		t1.z	=	lz1	*	map->GetMapScale();
	}
	else
	{
		t1.x	=	(lx1+1)	*	map->GetMapScale();
		t1.y	=	map->GetHeight(lz1+map->GetMidCell()+1,lx1+map->GetMidCell()+1);
		t1.z	=	(lz1+1)	*	map->GetMapScale();
	}

	t2.x	=	(lx1 + 1)	*	map->GetMapScale();
	t2.y	=	map->GetHeight(lz1+map->GetMidCell(),(lx1 + map->GetMidCell() + 1));
	t2.z	=	lz1	*	map->GetMapScale();

	t3.x	=	lx1	*	map->GetMapScale();
	t3.y	=	map->GetHeight(lz1+map->GetMidCell()+1,lx1+map->GetMidCell());
	t3.z	=	(lz1 + 1)	*	map->GetMapScale();

	//--------------------

	glColor3ub(255,0,0);
	glBegin(GL_TRIANGLES);
	glVertex3f(t1.x,t1.y,t1.z);
	glVertex3f(t2.x,t2.y,t2.z);
	glVertex3f(t3.x,t3.y,t3.z);
	glEnd();
}

void CGameLogic :: OnDraw()
{
	DrawTriangle();
	map->OnDraw();
	model->OnAnimate();
}