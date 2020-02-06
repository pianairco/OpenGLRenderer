#pragma once

#include"../Headers/jrmathematicslibrary.h"

//-----------------------------------------------------------

vec2		MultiplyScalarInVector2D(GLdouble s,vec2 vector)
{
	vec2	v;
	v.x		=	vector.x	*	s;
	v.y		=	vector.y	*	s;
	return	v;
}

vec3		MultiplyScalarInVector3D(GLdouble s,vec3 vector)
{
	vec3	v;
	v.x		=	vector.x	*	s;
	v.y		=	vector.y	*	s;
	v.z		=	vector.z	*	s;
	return	v;
}

vec2		SumVectors2D(vec2 vector1,vec2 vector2)
{
	vec2	v;
	v.x		=	vector1.x	+	vector2.x;
	v.y		=	vector1.y	+	vector2.y;
	return	v;
}

vec3		SumVectors3D(vec3 vector1,vec3 vector2)
{
	vec3	v;
	v.x		=	vector1.x	+	vector2.x;
	v.y		=	vector1.y	+	vector2.y;
	v.z		=	vector1.z	+	vector2.z;
	return	v;
}

vec2		SubtractVectors2D(vec2 vector1,vec2 vector2)
{
	vec2	v;
	v.x		=	vector1.x	-	vector2.x;
	v.y		=	vector1.y	-	vector2.y;
	return	v;
}

vec3		SubtractVectors3D(vec3 vector1,vec3 vector2)
{
	vec3	v;
	v.x		=	vector1.x	-	vector2.x;
	v.y		=	vector1.y	-	vector2.y;
	v.z		=	vector1.z	-	vector2.z;
	return	v;
}

GLfloat		MagnitudeOfVector2D(vec2 vector)// norm or lenght
{
	return	sqrtf(pow(vector.x,2) + pow(vector.y,2));
}

GLfloat		MagnitudeOfVector3D(vec3 vector)// norm or lenght
{
	return	sqrtf(pow(vector.x,2) + pow(vector.y,2) + pow(vector.z,2));
}

GLfloat		MagnitudeOfVectorRespectToOther2D(vec2 vector1,vec2 vector2)// norm or lenght
{
	vec2	v;
	v		=	SubtractVectors2D(vector1,vector2);

	return	sqrtf(pow(v.x,2) + pow(v.y,2));
}

GLfloat		MagnitudeOfVectorRespectToOther3D(vec3 vector1,vec3	vector2)// norm or lenght
{
	vec3	v;
	v		=	SubtractVectors3D(vector1,vector2);

	return	sqrtf(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
}

vec2		NormalizationVector2D(vec2 vector)
{
	GLfloat	mag		=	MagnitudeOfVector2D(vector);
	if(mag	==	0)
	{
		mag		=	1;
	}

	vec2	nrmVector;
	nrmVector.x		=	(1 / mag)	*	vector.x;
	nrmVector.y		=	(1 / mag)	*	vector.y;
	return	nrmVector;
}

vec3		NormalizationVector3D(vec3 vector)
{
	GLfloat	mag		=	MagnitudeOfVector3D(vector);
	if(mag	==	0)
	{
		mag		=	1;
	}

	vec3	nrmVector;
	nrmVector.x		=	(1 / mag)	*	vector.x;
	nrmVector.y		=	(1 / mag)	*	vector.y;
	nrmVector.z		=	(1 / mag)	*	vector.z;
	return	nrmVector;
}

vec2		NormalizationVectorRespectToOther2D(vec2 vector1,vec2 vector2)
{
	GLfloat	mag		=	MagnitudeOfVectorRespectToOther2D(vector1,vector2);
	if(mag	==	0)
	{
		mag		=	1;
	}

	vec2	v,nrmVector;
	v				=	SubtractVectors2D(vector1,vector2);
	nrmVector.x		=	(1 / mag)	*	v.x;
	nrmVector.y		=	(1 / mag)	*	v.y;
	return	nrmVector;
}

vec3		NormalizationVectorRespectToOther3D(vec3 vector1,vec3 vector2)
{
	GLfloat	mag		=	MagnitudeOfVectorRespectToOther3D(vector1,vector2);
	if(mag	==	0)
	{
		mag		=	1;
	}

	vec3	v,nrmVector;
	v				=	SubtractVectors3D(vector1,vector2);
	nrmVector.x		=	(1 / mag)	*	v.x;
	nrmVector.y		=	(1 / mag)	*	v.y;
	nrmVector.z		=	(1 / mag)	*	v.z;
	return	nrmVector;
}

GLfloat		DotProduct2D(vec2 vector1,vec2 vector2)
{
	return 	(vector1.x	*	vector2.x)	+	(vector1.y	*	vector2.y);
}

GLfloat		DotProduct3D(vec3 vector1,vec3 vector2)
{
	return 	(vector1.x	*	vector2.x)	+	(vector1.y	*	vector2.y)	+	(vector1.z	*	vector2.z);
}

GLfloat		DotProductRespectToOther2D(vec2 vector1,vec2 vector2,vec2 vector3)
{
	vec2	v1,v2;
	v1		=	SubtractVectors2D(vector1,vector3);
	v2		=	SubtractVectors2D(vector2,vector3);

	return (v1.x	*	v2.x)	+	(v1.y	*	v2.y);
}

GLfloat		DotProductRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3)
{
	vec3	v1,v2;
	v1		=	SubtractVectors3D(vector1,vector3);
	v2		=	SubtractVectors3D(vector2,vector3);

	return (v1.x	*	v2.x)	+	(v1.y	*	v2.y) + (v1.z	*	v2.z);
}

GLfloat		AngleBetweenVectorsR2D(vec2 vector1,vec2 vector2)
{
	GLfloat	mag1,mag2,dp;
	mag1	=	MagnitudeOfVector2D(vector1);
	mag2	=	MagnitudeOfVector2D(vector2);

	dp		=	DotProduct2D(vector1,vector2);
	if(dp	==	0)
	{
		return Q_PI / 2;
	}

	return	acos(dp		/	(mag1	*	mag2));
}

GLfloat		AngleBetweenVectorsR3D(vec3 vector1,vec3 vector2)
{
	GLfloat	mag1,mag2,dp;
	mag1	=	MagnitudeOfVector3D(vector1);
	mag2	=	MagnitudeOfVector3D(vector2);

	dp		=	DotProduct3D(vector1,vector2);
	if(dp	==	0)
	{
		return Q_PI / 2;
	}
	return	acos(dp		/	(mag1	*	mag2));
}

GLfloat		AngleBetweenVectorsRespectToOtherR2D(vec2 vector1,vec2 vector2,vec2 vector3)
{
	vec2	v1,v2;
	v1		=	SubtractVectors2D(vector1,vector3);
	v2		=	SubtractVectors2D(vector2,vector3);

	GLfloat	mag1,mag2,dp;
	mag1	=	MagnitudeOfVector2D(v1);
	mag2	=	MagnitudeOfVector2D(v2);

	dp		=	DotProduct2D(v1,v2);
	if(dp	==	0)
	{
		return Q_PI / 2;
	}

	return	acos(dp		/	(mag1	*	mag2));
}

GLfloat		AngleBetweenVectorsRespectToOtherR3D(vec3 vector1,vec3 vector2,vec3 vector3)
{
	vec3	v1,v2;
	v1		=	SubtractVectors3D(vector1,vector3);
	v2		=	SubtractVectors3D(vector2,vector3);

	GLfloat	mag1,mag2,dp;
	mag1	=	MagnitudeOfVector3D(v1);
	mag2	=	MagnitudeOfVector3D(v2);

	dp		=	DotProduct3D(v1,v2);
	if(dp	==	0)
	{
		return Q_PI / 2;
	}

	return	acos(dp		/	(mag1	*	mag2));
}

vec2		PerpendicularPoint2D(vec2 vector1,vec2 vector2)
{
	GLfloat	dp,mag2;
	dp		=	DotProduct2D(vector1,vector2);

	mag2	=	pow(MagnitudeOfVector2D(vector2),2);
	if(mag2	==	0)
	{
		mag2	=	0.00000001;
	}
	vec2	v;
	v		=	MultiplyScalarInVector2D((dp / mag2),vector2);
	return v;
}

vec3		PerpendicularPoint3D(vec3 vector1,vec3 vector2)
{
	GLfloat	dp,mag2;
	dp		=	DotProduct3D(vector1,vector2);

	mag2	=	pow(MagnitudeOfVector3D(vector2),2);
	if(mag2	==	0)
	{
		mag2	=	0.00000001;
	}
	vec3	v;
	v		=	MultiplyScalarInVector3D((dp / mag2),vector2);
	return v;
}

vec2		PerpendicularPointRespectToOther2D(vec2 vector1,vec2 vector2,vec2 vector3)
{
	vec2	v1,v2,v;
	v1		=	SubtractVectors2D(vector1,vector3);
	v2		=	SubtractVectors2D(vector2,vector3);

	GLfloat	dp,mag2;
	dp		=	DotProduct2D(v1,v2);
	mag2	=	pow(MagnitudeOfVector2D(v2),2);
	if(mag2	==	0)
	{
		mag2	=	0.00000001;
	}
	v		=	MultiplyScalarInVector2D((dp / mag2),v2);
	return	SumVectors2D(v,vector3);
}

vec3		PerpendicularPointRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3)
{
	vec3	v1,v2,v;
	v1		=	SubtractVectors3D(vector1,vector3);
	v2		=	SubtractVectors3D(vector2,vector3);

	GLfloat	dp,mag2;
	dp		=	DotProduct3D(v1,v2);
	mag2	=	pow(MagnitudeOfVector3D(v2),2);
	if(mag2	==	0)
	{
		mag2	=	0.00000001;
	}
	v		=	MultiplyScalarInVector3D((dp / mag2),v2);
	return	SumVectors3D(v,vector3);
}

GLfloat		DistanceBetweenVectors2D(vec2 vector1,vec2 vector2)
{
	vec2	v;
	v		=	SubtractVectors2D(vector1,vector2);
	return MagnitudeOfVector2D(v);
}

GLfloat		DistanceBetweenVectors3D(vec3 vector1,vec3 vector2)
{
	vec3	v;
	v		=	SubtractVectors3D(vector1,vector2);
	return MagnitudeOfVector3D(v);
}

vec3		CrossProduct3D(vec3 vector1,vec3 vector2)
{
	vec3	v;
	v.x		=	vector1.y	*	vector2.z	-	vector1.z	*	vector2.y;
	v.y		=	vector1.z	*	vector2.x	-	vector1.x	*	vector2.z;
	v.z		=	vector1.x	*	vector2.y	-	vector1.y	*	vector2.x;
	return	v;
}

vec3		CrossProductRespectToOther3D(vec3 vector1,vec3 vector2,vec3 vector3)
{
	vec3	v1,v2,v;
	v1		=	SubtractVectors3D(v1,vector3);
	v2		=	SubtractVectors3D(v2,vector3);
	v.x		=	v1.y	*	v2.z	-	v1.z	*	v2.y;
	v.y		=	v1.z	*	v2.x	-	v1.x	*	v2.z;
	v.z		=	v1.x	*	v2.y	-	v1.y	*	v2.x;
	return	SumVectors3D(v,vector3);
}