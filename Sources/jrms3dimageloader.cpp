#pragma once

#include"../Headers/jrms3dimageloader.h"

unsigned char *LoadBitmapFileForMS3D(char *filename,BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *fp;//--------------------------------the file pointer
	BITMAPFILEHEADER bitmapFileHeader;//-------bitmap file header
	unsigned char *bitmapImage;//--------------bitmap image data
	int imageIdx=0;//--------------------------image index counter
	unsigned char tempRGB;//-------------------swap variable

	char array1[] = "./Models/";
	char* newArray = new char[strlen(array1) + strlen(filename) + 1];
	strcpy(newArray, array1);
	strcat(newArray, filename);
	//open filename in "read binary" mode
	fp=fopen(newArray,"rb");
	if(fp==NULL)
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
	bitmapImage		=	new unsigned char[bitmapInfoHeader->biSizeImage];

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
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	int MAP_Z,MAP_X;
	
	MAP_Z=bitmapInfoHeader->biHeight;
	MAP_X=bitmapInfoHeader->biWidth;
	int tempR=0,tempG=0,tempB=0;
	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (int z = 0; z < MAP_Z/2; z++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			tempR = bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)];
			tempG = bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)+1];
			tempB = bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)+2];

			bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)]	 = bitmapImage[((z*MAP_Z+x)*3)] ;
			bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)+1] = bitmapImage[((z*MAP_Z+x)*3)+1] ;
			bitmapImage[(((MAP_Z-1-z)*MAP_Z+x)*3)+2] = bitmapImage[((z*MAP_Z+x)*3)+2] ;

			bitmapImage[((z*MAP_Z+x)*3)]   = tempR;
			bitmapImage[((z*MAP_Z+x)*3)+1] = tempG;
			bitmapImage[((z*MAP_Z+x)*3)+2] = tempB;
		}
	}

	// close the file and return the bitmap image data
	fclose(fp);
	return bitmapImage;
}

void LoadTextureFromBitmapFileForMS3D(char *filename,unsigned int &texture)
{
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char *bitmapData;

	bitmapData=LoadBitmapFileForMS3D(filename,&bitmapInfoHeader);

	glGenTextures(1,&texture);

	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,bitmapData);
}