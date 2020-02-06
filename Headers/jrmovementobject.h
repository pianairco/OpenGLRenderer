#pragma once
#include<time.h>
#include"../Headers/jrobject.h"

struct ST_Anim_State
{
	int		time;
	int		minFrame;
	int		maxFrame;
};

class CMovementObject : public CObject
{
private:

	ST_Anim_State	*anim_state;
	int				numberOfState;
	int				lastIndex;

	int				indexOfState;

	vec_t			movement_speed;
	vec_t			spin_speed;

	int				frame_index;
	clock_t			last_time;
	clock_t			counter;
	clock_t			frame_time;

public:

	CMovementObject(CMS3DModelLoader *ldr, CMS3DModelRenderer *rnd, int numOfState);
	~CMovementObject();
	void InitObject();

	void SetupTotalAnimState();
	void SetupAnimState(int min_frame,int max_frame);
	void SetupAnimationFPS(int numState,int FPS);

	void SetMovementSpeed(vec_t spd);
	void SetSpinSpeed(vec_t spd);

	void SetState(int s);

	void SetFrame();
	void ResetFrame();
	
	void GoForward();
	void GoBackward();
	void GoRight();
	void GoLeft();
	void GoUp();
	void GoDown();
	
	void SpinRight();
	void SpinLeft();
	void SpinUp();
	void SpinDown();
	void SpinDiagonalLeft();
	void SpinDiagonalRight();

	void OnAnimate();

};