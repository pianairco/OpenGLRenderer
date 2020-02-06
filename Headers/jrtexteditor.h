#pragma once

#include<gl/freeglut.h>

#pragma comment(lib,"glut32.lib")

#using<mscorlib.dll>
using namespace System;

//---------------------------------------------------------------

public ref class CString
{
private:

	static void			*font;
	static GLfloat		red_color;
	static GLfloat		green_color;
	static GLfloat		blue_color;

public:

	void static InitClass()
	{
		font			=	GLUT_BITMAP_TIMES_ROMAN_10;
		red_color		=	0.85f;
		green_color		=	0.65f;
		blue_color		=	0.0f;
	}

	char static *NumberToChar(double number)
	{
		String ^str;
		str=number.ToString();
		char *ch=new char[str->Length];
		for(int i=0;i<str->Length;i++)
			ch[i]=str[i];
		return ch;
	}

	void static PrintOnPlanX(GLfloat x,GLfloat y,GLfloat z,char* text)
	{
		char *ch;
		glColor3f(red_color, green_color, blue_color);

//		glPushMatrix();

		glRasterPos3f(x,y,z);

		ch	=	text;
		while(*ch	!=	'\0')
		{
			glutBitmapCharacter(font,*ch);
			ch++;
		}

//		glPopMatrix();
	}

	void static PrintOnPlanX(GLfloat x,GLfloat y,GLfloat z, void *f,char* text)
	{
		char *ch;
		glColor3f(red_color, green_color, blue_color);

//		glPushMatrix();

		glRasterPos3f(x,y,z);

		ch	=	text;
		while(*ch	!=	'\0')
		{
			glutBitmapCharacter(f,*ch);
			ch++;
		}

//		glPopMatrix();
	}

};

/*
void PrintOnPlanX(GLfloat x,GLfloat y,GLfloat z,char* text)
{
}
*/
