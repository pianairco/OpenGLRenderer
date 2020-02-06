#pragma once

#include"../Headers/jrmathlib.h"

//----------------------------------------------------------------------

vec2		MultiplyScalarInVector2D(GLdouble s,vec2 v);
vec3		MultiplyScalarInVector3D(GLdouble s,vec3 v);

vec2		SumVectors2D(vec2 vector1,vec2 vector2);
vec3		SumVectors3D(vec3 vector1,vec3 vector2);

vec2		SubtractVectors2D(vec2 vector1,vec2 vector2);
vec3		SubtractVectors3D(vec3 vector1,vec3 vector2);

GLfloat		MagnitudeOfVector2D(vec2 vector);// norm or lenght
GLfloat		MagnitudeOfVector3D(vec3 vector);// norm or lenght

GLfloat		MagnitudeOfVectorRespectToOther2D(vec2 vector1,vec2 vector2);// norm or lenght
GLfloat		MagnitudeOfVectorRespectToOther3D(vec3 vector1,vec3	vector2);// norm or lenght

vec2		NormalizationVector2D(vec2 vector);
vec3		NormalizationVector3D(vec3 vector);

vec2		NormalizationVectorRespectToOther2D(vec2 vector1,vec2 vector2);
vec3		NormalizationVectorRespectToOther3D(vec3 vector1,vec3 vector2);

GLfloat		DotProduct2D(vec2 vector1,vec2 vector2);
GLfloat		DotProduct3D(vec3 vector1,vec3 vector2);

GLfloat		DotProductRespectToOther2D(vec2 vector1,vec2 vector2,vec2 vector3);
GLfloat		DotProductRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3);

GLfloat		AngleBetweenVectorsR2D(vec2 vector1,vec2 vector2);
GLfloat		AngleBetweenVectorsR3D(vec3 vector1,vec3 vector2);

GLfloat		AngleBetweenVectorsRespectToOtherR2D(vec2 vector1,vec2 vector2,vec2 vector3);
GLfloat		AngleBetweenVectorsRespectToOtherR3D(vec3 vector1,vec3 vector2,vec3 vector3);

vec2		PerpendicularPoint2D(vec2 vector1,vec2 vector2);
vec3		PerpendicularPoint3D(vec3 vector1,vec3 vector2);

vec2		PerpendicularPointRespectToOther2D(vec2 vector1,vec2 vector2,vec2 vector3);
vec3		PerpendicularPointRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3);

GLfloat		DistanceBetweenVectors2D(vec2 vector1,vec2 vector2);
GLfloat		DistanceBetweenVectors3D(vec3 vector1,vec3 vector2);

//vec2		CrossProduct2D(vec2 vector1,vec2 vector2);
vec3		CrossProduct3D(vec3 vector1,vec3 vector2);

//vec2		CrossProductRespectToOther2D(vec2 vector1,vec2 vector2,vec3 vector3);
vec3		CrossProductRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3);
