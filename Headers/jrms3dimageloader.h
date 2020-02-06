#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<gl/freeglut.h>
#include"../Headers/jrtexteditor.h"

#pragma comment(lib,"glut32.lib")


unsigned char	*LoadBitmapFileForMS3D(char *filename,BITMAPINFOHEADER *bitmapInfoHeader);
void			LoadTextureFromBitmapFileForMS3D(char *filename,unsigned int &texture);

