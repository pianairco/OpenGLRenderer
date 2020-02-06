#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<gl/freeglut.h>

#pragma comment(lib,"glut32.lib")


unsigned char	*LoadBitmapFile(char *filename,BITMAPINFOHEADER *bitmapInfoHeader);
void			LoadTextureFromBitmapFile(char *filename,unsigned int &texture);

