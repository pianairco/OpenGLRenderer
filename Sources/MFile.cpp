#define WIN32_LEAN_AND_MEAN
#pragma once

#include<windows.h>
#include"../Headers/cameraV2.h"
#include<time.h>

#include"../Headers/jrtexteditor.h"

#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#using<mscorlib.dll>
using namespace System;
int xxx=0;

HGLRC hRC=NULL;
HDC hDC=NULL;
HWND hWnd=NULL;
HINSTANCE hInstance=NULL;

BOOLEAN keys[256];
BOOLEAN active=TRUE;
BOOLEAN fullScreen=TRUE;

////// Mouse/Camera Variables
CCamera *myCam=new CCamera();
Int32 width,height;
GLint mouse_X,mouse_Y;

BITMAPINFOHEADER bitmapInfoHeader; // temp bitmap info header
unsigned char* imageData; // the map image data

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void KillGLWindow();
int SetupRC();
void ReSizeGLScene(Int32,Int32);
int DisplayFunc(INT32 width,INT32 height);

void SetupPixelFormat(INT32 bits)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	nPixelFormat=ChoosePixelFormat(hDC,&pfd);
	SetPixelFormat(hDC,nPixelFormat,&pfd);
}

bool CreateGLWindow(char* title,int width,int height,int bits,bool fullScreenFlag)
{
	WNDCLASSA wc;

	DWORD dwExStyle;
	DWORD dwStyle;

	RECT windowRect;
	windowRect.left=(long)0;
	windowRect.right=(long)width;
	windowRect.top=(long)0;
	windowRect.bottom=(long)height;

	fullScreen=fullScreenFlag;

	hInstance=GetModuleHandle(NULL);

	wc.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wc.lpfnWndProc=(WNDPROC)WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_WINLOGO);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=NULL;
	wc.lpszMenuName=NULL;
	wc.lpszClassName="OpenGL";

	if(!RegisterClassA(&wc))
	{
		MessageBoxA(hWnd,"Failed to register the window class.","ERROR",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	if(fullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth=width;
		dmScreenSettings.dmPelsHeight=height;
		dmScreenSettings.dmBitsPerPel=bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if(MessageBoxA(NULL,"The requested fullscreen mode is not suported,use windowed mode instead?","info",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullScreen=false;
			}
			else
			{
				MessageBoxA(NULL,"Program will now close.","info",MB_OK|MB_ICONINFORMATION);
				return FALSE;
			}
		}
	}

	if(fullScreen)
	{
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
		//ShowCursor(false);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}
	
	AdjustWindowRectEx(&windowRect,dwStyle,TRUE,dwExStyle);		//not effect in fullscreen

	if(!(hWnd=CreateWindowExA(dwExStyle,						//exstyle
							"OpenGL",							//class name
							title,								//title
							WS_CLIPSIBLINGS|
							WS_CLIPCHILDREN|
							dwStyle,							//style
							0,0,								//position
							windowRect.right-windowRect.left,	//window width
							windowRect.bottom-windowRect.top,	//window height
							NULL,								//no parent window
							NULL,								//no menu
							hInstance,							//instance
							NULL)))								//dont pass anything to WM_CREATE
	{
		KillGLWindow();
		MessageBoxA(NULL,"Window creation error","info",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	if(!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBoxA(NULL,"Can't create a gl device context.","info",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	SetupPixelFormat(bits);

	if(!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBoxA(NULL,"Can't create a gl rendering context.","info",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();
		MessageBoxA(NULL,"Can't active the gl rendering context.","info",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width,height);

	if(!SetupRC())
	{
		KillGLWindow();
		MessageBoxA(NULL,"initialization failed.","info",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	MSG msg;											//windows message structure
	bool done=FALSE;									//if done==true exit from loop


	myCam->MCSetEyeCamera(0,125,50);
	SetCursorPos(0,0);

	if(MessageBoxA(NULL,"Do you want start in fullscreen?","Question",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullScreen=false;
	}

	if(!CreateGLWindow("My Objects",1024,600,32,fullScreen))
	{
		return 0;
	}

	while(!done)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message==WM_QUIT)
			{
				done=true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(active)
			{
				if(keys['W'])
				{
					myCam->MCMoveCameraToForward(1);
					myCam->MCLookAt();
				}

				if(keys['S'])
				{
					myCam->MCMoveCameraToBackward(1);
					myCam->MCLookAt();
				}

				if(keys[VK_ESCAPE])
				{
					done=TRUE;
				}
				else
				{
					if(mouse_X==myCam->MCGetMouseX() && mouse_Y==myCam->MCGetMouseY())
					{
						xxx++;
					}
					else
					{
						xxx=0;
					}
					if(xxx>1000)
						xxx==3;
					
					if(xxx<2)
					{
						myCam->MCSpinCamera();
						myCam->MCLookAt();
						mouse_X=myCam->MCGetMouseX();
						mouse_Y=myCam->MCGetMouseY();
					}
					
				}
			
				DisplayFunc(width,height);
				SwapBuffers(hDC);
			
			}
		}
		
	}
	
	KillGLWindow();
	return (msg.wParam);
}

void KillGLWindow(void)
{
	if(fullScreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(true);
	}

	if(hRC)
	{
		if(!wglMakeCurrent(NULL,NULL))
		{
			MessageBoxA(hWnd,"Release of DC and RC failed.","SHUTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
		}

		if(!wglDeleteContext(hRC))
		{
			MessageBoxA(hWnd,"Release Rendering Context failed.","SHUTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
			hRC=NULL;//?
		}
	}

	if(hDC && !ReleaseDC(hWnd,hDC))
	{
		MessageBoxA(hWnd,"Release Device Context failed.","SHUTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
		hDC=NULL;
	}

	if(hWnd && !DestroyWindow(hWnd))
	{
		MessageBoxA(hWnd,"Could not Release hWnd.","SHUTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
		hWnd=NULL;
	}

	if(!UnregisterClass((LPCWSTR)"OpenGL",hInstance))
	{
		MessageBoxA(hWnd,"Could not Unregistered class.","SHOTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
		hInstance=NULL;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_ACTIVATE:
	{
		if(!HIWORD(wParam))										//check minimization state
		{
			active=true;
		}
		else
		{
			active=false;
		}
		return 0;												//return to the message loop
	}
	case WM_SYSCOMMAND:
	{
		switch(wParam)
		{
		case SC_SCREENSAVE:										//screen saver trying to start
		case SC_MONITORPOWER:									//monitor trying to enter power save
			return 0;											//prevent from hapening
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);										//send a quit message
		return 0;												//jump back
	}
	case WM_KEYDOWN:
	{
		keys[wParam]=TRUE;
		return 0;
	}
	case WM_KEYUP:
	{
		keys[wParam]=FALSE;
		return 0;
	}
	case WM_SIZE:
	{
			width=LOWORD(lParam);
			height=HIWORD(lParam);
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
	}
	case WM_MOUSEMOVE:
	{	
		myCam->MCSetMouseMove(LOWORD(lParam),HIWORD(lParam));
		
		return 0;
	}
	
	default:
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}