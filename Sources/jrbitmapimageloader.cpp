#pragma once

#include"../Headers/jrbitmapimageloader.h"

unsigned char *LoadBitmapFile(char *filename,BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *fp;//--------------------------------the file pointer
	BITMAPFILEHEADER bitmapFileHeader;//-------bitmap file header
	unsigned char *bitmapImage;//--------------bitmap image data
	int imageIdx=0;//--------------------------image index counter
	unsigned char tempRGB;//-------------------swap variable

	//open filename in "read binary" mode
	fp	=	fopen(filename,"rb");
	if(fp == NULL)
	{
		return NULL;
	}

	//read the bitmap file header
	fread(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,fp);

	//verify that this is a bitmap file by checking for the universal bitmap id
	if(bitmapFileHeader.bfType!=0x4d42)
	{
		fclose(fp);
		return NULL;
	}

	//read the bitmap information header
	fread(bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fp);
	if(bitmapInfoHeader->biSizeImage	==	0)
	{
		bitmapInfoHeader->biSizeImage	=	bitmapInfoHeader->biWidth	*	bitmapInfoHeader->biHeight	*	3;
	}

	//move file pointer to beginning of bitmap data
	fseek(fp,bitmapFileHeader.bfOffBits,SEEK_SET);
		
	//allocate enough memory for the bitmap image data
	bitmapImage=(unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	//verify memory allocation
	if(!bitmapImage)
	{
		free(bitmapImage);
		fclose(fp);
		return NULL;
	}

	//read in the bitmap image data
	fread(bitmapImage,1,bitmapInfoHeader->biSizeImage,fp);

	//make sure bitmap image data was read
	if(bitmapImage==NULL)
	{
		fclose(fp);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB						=	bitmapImage[imageIdx];
		bitmapImage[imageIdx]		=	bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2]	=	tempRGB;
	}
	
	// close the file and return the bitmap image data
	fclose(fp);
	return bitmapImage;
}

void LoadTextureFromBitmapFile(char *filename,unsigned int &texture)
{
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char *bitmapData;

	bitmapData	=	LoadBitmapFile(filename,&bitmapInfoHeader);

	glGenTextures(1,&texture);

	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,bitmapData);
}