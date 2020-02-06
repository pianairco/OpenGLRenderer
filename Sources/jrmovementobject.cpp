#pragma once

#include"../Headers/jrmovementobject.h"

CMovementObject :: CMovementObject(CMS3DModelLoader *ldr, CMS3DModelRenderer *rnd, int numOfState) : CObject(ldr,rnd)
{
	numberOfState		=	numOfState;
	lastIndex			=	0;
	if(numberOfState < 1)
	{
		numberOfState	=	1;
	}

	anim_state			=	new ST_Anim_State[numberOfState];

	SetupTotalAnimState();

	indexOfState		=	0;

	movement_speed		=	1.0f;
	spin_speed			=	Q_PI / 180.0f;
	frame_index			=	0;
	last_time			=	0;
	counter				=	0;
}

CMovementObject :: ~CMovementObject()
{
	//-----?
}

void CMovementObject :: InitObject()
{
	SetMinMax();
	SetCubeBound();
	//SetCenterAndRadius();
	SetTextPosition();
}

void CMovementObject :: SetMovementSpeed(vec_t spd)
{
	movement_speed	=	spd;
}

void CMovementObject :: SetSpinSpeed(vec_t spd)
{
	spin_speed	=	spd;
}

void CMovementObject :: SetupTotalAnimState()
{
	anim_state[0].minFrame	=	0;
	anim_state[0].maxFrame	=	model_loader->GetNumberOfTotalFrame() - 1;
	anim_state[0].time		=	CLOCKS_PER_SEC / model_loader->GetAnimationFPS();

	frame_time				=	anim_state[0].time;
	lastIndex++;
}

void CMovementObject :: SetupAnimState(int min_frame, int max_frame)
{
	if(min_frame < 1)
	{
		min_frame	=	1;
	}
	if(max_frame > model_loader->GetNumberOfTotalFrame())
	{
		max_frame	=	model_loader->GetNumberOfTotalFrame();
	}

	if(lastIndex < numberOfState)
	{
		anim_state[lastIndex].minFrame	=	min_frame-1;
		anim_state[lastIndex].maxFrame	=	max_frame-1;
		anim_state[lastIndex].time		=	CLOCKS_PER_SEC / (anim_state[lastIndex].maxFrame - anim_state[lastIndex].minFrame + 1);
/*		if(anim_state[lastIndex].time > model_loader->GetAnimationFPS())
		{
			anim_state[lastIndex].time	=	model_loader->GetAnimationFPS();
		}*/
		lastIndex++;
	}
}

void CMovementObject :: SetupAnimationFPS(int numState,int FPS)
{
	if(numState < numberOfState)
	{
		anim_state[numState].time	=	CLOCKS_PER_SEC / FPS;
	}
}

void CMovementObject :: SetState(int s)
{
	if(s < numberOfState)
	{
		indexOfState	=	s;
		frame_time		=	anim_state[indexOfState].time;
	}
}

/*void CMovementObject :: SetFrame()
{
	clock_t time	=	clock();

	counter			+=	( time - last_time ) ;/// CLOCKS_PER_SEC ;
	if(counter >= 1000)
	{
		counter	=	0;
	}

	last_time		=	time;
	frame_index		=	counter / frame_time + anim_state[indexOfState].minFrame;
	if(frame_index < anim_state[indexOfState].minFrame)
		frame_index	=	anim_state[indexOfState].maxFrame;
	else if(frame_index > anim_state[indexOfState].maxFrame)
		frame_index	=	anim_state[indexOfState].minFrame;

}*/

void CMovementObject :: SetFrame()
{
	clock_t time	=	clock();

	if( (time - last_time) >= anim_state[indexOfState].time)
	{
		frame_index++;
		last_time		=	time;
	}	

	if(frame_index < anim_state[indexOfState].minFrame)
		frame_index	=	anim_state[indexOfState].maxFrame;
	else if(frame_index > anim_state[indexOfState].maxFrame)
		frame_index	=	anim_state[indexOfState].minFrame;
}

void CMovementObject :: ResetFrame()
{
	frame_time			=	CLOCKS_PER_SEC / model_loader->GetNumberOfTotalFrame();
	frame_index			=	0;
}

void CMovementObject :: GoForward()
{
	position.x	+=	sin(rotation.y) * movement_speed;
	position.z	+=	cos(rotation.y) * movement_speed;
}

void CMovementObject :: GoBackward()
{
	position.x	-=	sin(rotation.y) * movement_speed;
	position.z	-=	cos(rotation.y) * movement_speed;
}

void CMovementObject :: GoRight()
{
	position.x	-=	cos(rotation.y) * movement_speed;
	position.z	+=	sin(rotation.y) * movement_speed;
}

void CMovementObject :: GoLeft()
{
	position.x	+=	cos(rotation.y) * movement_speed;
	position.z	-=	sin(rotation.y) * movement_speed;
}

void CMovementObject :: GoUp()
{
	position.y	+=	movement_speed;
}

void CMovementObject :: GoDown()
{
	position.y	-=	movement_speed;
}

void CMovementObject :: SpinRight()
{
	rotation.y	-=	spin_speed;
}

void CMovementObject :: SpinLeft()
{
	rotation.y	+=	spin_speed;
}

void CMovementObject :: SpinUp()
{
	rotation.x	+=	spin_speed;
}

void CMovementObject :: SpinDown()
{
	rotation.x	-=	spin_speed;
}

void CMovementObject :: SpinDiagonalLeft()
{
	rotation.z	-=	spin_speed;
}

void CMovementObject :: SpinDiagonalRight()
{
	rotation.z	+=	spin_speed;
}

void CMovementObject :: OnAnimate()
{
	SetFrame();
	model_renderer->DrawAnimateModel(position,rotation,frame_index);
}