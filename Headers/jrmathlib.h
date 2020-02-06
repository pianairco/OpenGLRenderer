#pragma once

#include<math.h>
#include<gl/freeglut.h>

#pragma comment(lib,"glut32.lib")


//----------------------------------
//--------------define new types
//----------------------------------
	
typedef GLfloat vec_t;

typedef GLushort*	MSushort;
typedef vec_t*	MSfloat;
typedef char*		MSchar;

struct vec3
{
	vec_t x,y,z;
};

struct vec2
{
	vec_t x,y;
};


typedef vec_t vec3_t[3];	// x,y,z
typedef vec_t vec4_t[4];	// x,y,z,w


//-------------------------------------

#define	Q_PI	3.14159265358979323846
#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])

//-------------------------------------

void AngleMatrix (const GLfloat angles[3], float (*matrix)[4] );
void R_ConcatTransforms (const float in1[3][4], const float in2[3][4], float out[3][4]);
void AngleQuaternion( const vec3_t angles, vec4_t quaternion );
void QuaternionSlerp( const vec4_t p, vec4_t q, float t, vec4_t qt );
void QuaternionMatrix( const vec4_t quaternion, float (*matrix)[4] );
void VectorRotate (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorIRotate (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorTransform (const vec3_t in1, const float in2[3][4], vec3_t out);
void VectorITransform (const vec3_t in1, const float in2[3][4], vec3_t out);
vec_t RadianToDegree( vec_t angle);
