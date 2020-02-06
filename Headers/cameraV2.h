#pragma once

#include<gl/freeglut.h>
#include<math.h>

#using<mscorlib.dll>
using namespace System;


class CCamera{
protected:
	GLfloat eyeX,eyeY,eyeZ;//							eye camera
	GLfloat lookAtX,lookAtY,lookAtZ;//					center camera
	GLfloat upX,upY,upZ;//								up camera
	GLfloat spinAroundAxisY;//							radian of spin camera around y axis
	GLfloat spinAroundAxisX;//							radian of spin camera around x axis
	GLboolean isMove,isVertical,isHorizontal;//			whether mouse move and move is vertical and horizontal
	GLfloat spdHMove,spdVMove;//						
	GLint mouseX,mouseY;
public:
	CCamera()
	{
		MCResetMouse();
		MCResetCamera();
	}

	void MCResetMouse()
	{
		isMove=false;
		isVertical=false;
		isHorizontal=false;
		spdHMove=0.1f;
		spdVMove=0.1f;
		mouseX=0;
		mouseY=0;
		//SetCursorPos(mouseX,mouseY);
	}

	void MCResetEyeCamera()
	{
		eyeX=0.0f;
		eyeY=0.0f;
		eyeZ=0.0f;
	}

	void MCResetLookAtCamera()
	{
		MCResetSpinCamera();
		lookAtX=eyeX+cos(spinAroundAxisX);
		lookAtY=eyeY+sin(spinAroundAxisY);
		lookAtZ=eyeZ+sin(spinAroundAxisX);
	}

	void MCResetSpinCamera()
	{
		spinAroundAxisX=0.0f;
		spinAroundAxisY=4.71f;
	}

	void MCResetUpCamera()
	{
		upX=0.0f;
		upY=1.0f;
		upZ=0.0f;
	}

	void MCResetCamera()
	{
		MCResetEyeCamera();
		MCResetLookAtCamera();
		MCResetUpCamera();
	}

	void MCSetEyeCamera(GLfloat x,GLfloat y,GLfloat z)
	{
		eyeX=x;
		eyeY=y;
		eyeZ=z;
		MCSetLookAtCamera();
	}

	void MCSetLookAtCamera()
	{
		lookAtX=eyeX+cos(spinAroundAxisY);
		lookAtY=eyeY+sin(spinAroundAxisX);
		lookAtZ=eyeZ+sin(spinAroundAxisY);
	}

	void MCSetSpinCameraAroundAxisX(GLfloat x)
	{
		spinAroundAxisX=x;
		//MCSetLookAtCamera();
	}

	void MCSetSpinCameraAroundAxisY(GLfloat y)
	{
		spinAroundAxisY=y;
		//MCSetLookAtCamera();
	}

	void MCLookAt()
	{
		MCSetLookAtCamera();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyeX,eyeY,eyeZ,
				  lookAtX,lookAtY,lookAtZ,
				  upX,upY,upZ);
	}
	void MCSpinCameraToLeft()
	{
		spinAroundAxisY+=spdHMove;
	}

	void MCSpinCameraToRight()
	{
		spinAroundAxisY+=spdHMove;
	}

	void MCSpinCameraToUp()
	{
		spinAroundAxisX+=spdVMove;
		
		if(spinAroundAxisX>=1.57)
		{
			spinAroundAxisX-=spdVMove;
		}
	}

	void MCSpinCameraToDown()
	{
		spinAroundAxisX+=spdVMove;

		if(spinAroundAxisX<=-1.57)
		{
			spinAroundAxisX-=spdVMove;
		}
	}

/*
	String ^str;
	str=horizontalMove.ToString();
	char *ch=new char[str->Length];
	for(int i=0;i<str->Length;i++)
		ch[i]=str[i];
*/

	void MCMoveCameraToForward(GLfloat speed)
	{
		eyeX+=cos(spinAroundAxisY)*speed;
		eyeZ+=sin(spinAroundAxisY)*speed;
	}

	void MCMoveCameraToBackward(GLfloat speed)
	{
		eyeX-=cos(spinAroundAxisY)*speed;
		eyeZ-=sin(spinAroundAxisY)*speed;
	}

	void MCSetMouseMove(GLint x,GLint y)
	{
		GLint oldX,oldY;
		oldX=mouseX;
		oldY=mouseY;
		mouseX=x;
		mouseY=y;

		MCSetMouseMoveForSpinCamera(oldX,oldY,mouseX,mouseY);
		
		if(mouseX>500)
		{
			SetCursorPos(200,mouseY);
			mouseX=200;
		}
		else if(mouseX<100)
		{
			SetCursorPos(400,mouseY);
			mouseX=400;
		}
		if(mouseY>500)
		{
			SetCursorPos(mouseX,200);
			mouseY=200;
		}
		else if(mouseY<100)
		{
			SetCursorPos(mouseX,400);
			mouseY=400;
		}
	}

	void MCSetMouseMoveForSpinCamera(GLint oldX,GLint oldY,GLint newX,GLint newY)
	{
		spdHMove=newX-oldX;
		if(spdHMove!=0)
		{
			//isMove=true;
			isHorizontal=true;
			//MCSetSpeedForSpin();
		}
		else
		{
			//isMove=false;
			isHorizontal=false;
		}
		spdVMove=oldY-newY;
		if(spdVMove!=0)
		{
			//isMove=true;
			isVertical=true;
			//MCSetSpeedForSpin();
		}
		else
		{
			//isMove=false;
			isVertical=false;
		}
		
		if(isHorizontal || isVertical)
		{
			isMove=true;
			MCSetSpeedForSpin();
		}
		else
		{
			isMove=false;
		}

	}

	void MCSetSpeedForSpin()
	{
		if(spdHMove>0)
		{
			if(spdHMove>0 && spdHMove<=3)
			{
				spdHMove=0.01f;
			}
			else if(spdHMove>3 && spdHMove<=10)
			{
				spdHMove=0.05f;
			}
			else
			{
				spdHMove=0.1f;
			}
		}
		else if(spdHMove<0)
		{
			if(spdHMove<0 && spdHMove>=-3)
			{
				spdHMove=-0.01f;
			}
			else if(spdHMove<-3 && spdHMove>=-10)
			{
				spdHMove=-0.05f;
			}
			else
			{
				spdHMove=-0.1f;
			}
			
		}

		if(spdVMove>0)
		{
			if(spdVMove>0 && spdVMove<=10)
			{
				spdVMove=0.01f;
			}
			else if(spdVMove>10 && spdVMove<=20)
			{
				spdVMove=0.1f;
			}
			else
			{
				spdVMove=0.1f;
			}
		}
		else if(spdVMove<0)
		{
			if(spdVMove<0 && spdVMove>=-10)
			{
				spdVMove=-0.01f;
			}
			else if(spdVMove<-10 && spdVMove>=-20)
			{
				spdVMove=-0.1f;
			}
			else
			{
				spdVMove=-0.1f;
			}
		}
	}

	void MCSpinCamera()
	{
		if(isMove)
		{
			if(isHorizontal)
			{
				if(spdHMove>0)
				{
					MCSpinCameraToRight();
				}
				else if(spdHMove<0)
				{
					MCSpinCameraToLeft();
				}
			}
			if(isVertical)
			{
				if(spdVMove>0)
				{
					MCSpinCameraToUp();
				}
				else if(spdVMove<0)
				{
					MCSpinCameraToDown();
				}
			}
		}
	}

	GLint MCGetMouseX()
	{
		return mouseX;
	}

	GLint MCGetMouseY()
	{
		return mouseY;
	}
};