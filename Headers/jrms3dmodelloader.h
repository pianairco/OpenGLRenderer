#pragma once

#include<math.h>
#include<stdio.h>
#include<vector>
#include<gl/freeglut.h>

#include"../Headers/jrmathlib.h"
#include"../Headers/jrms3dimageloader.h"

#pragma comment(lib,"glut32.lib")

#using<mscorlib.dll>
using namespace System;

//-----------------------------------------------
//---
//-----------------------------------------------

#define MAX_VERTICES				65534
#define MAX_TRIANGLES				65534
#define MAX_GROUPS					255
#define MAX_MATERIALS				128
#define MAX_JOINTS					128
#define MAX_TEXTURE_FILENAME_SIZE	128

#define SELECTED		1
#define HIDDEN			2
#define SELECTED2		4
#define DIRTY			8
#define ISKEY			16
#define NEWLYCREATED	32
#define MARKED			64

#define SPHEREMAP		0x80
#define HASALPHA		0x40
#define COMBINEALPHA    0x20

#define TRANSPARENCY_MODE_SIMPLE				0
#define TRANSPARENCY_MODE_DEPTHSORTEDTRIANGLES	1
#define TRANSPARENCY_MODE_ALPHAREF				2

//-----------------------------------------------------
//--------	structs
//-----------------------------------------------------

struct ms3d_vertex
{
	unsigned char flags;
	float vertex[3];
	//-----------------------------------
	//-- index of joints in milkshape
	//-----------------------------------
	char boneId;
	unsigned char referenceCount;

	char boneIds[3];
	unsigned char weights[3];
	unsigned int extra;
	float renderColor[3];
};

struct ms3d_triangle
{
	unsigned short flags;
	unsigned short vertexIndices[3];
	float vertexNormals[3][3];
	float s[3];
	float t[3];
	float normal[3];
	unsigned char smoothingGroup;
	unsigned char groupIndex;
};

struct ms3d_group
{
	unsigned char flags;
	char name[32];
	std::vector<unsigned short> triangleIndices;
	char materialIndex;
	std::vector<char> comment;
};

struct ms3d_material
{
	char name[32];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float shininess;
    float transparency;
	unsigned char mode;
	char texture[MAX_TEXTURE_FILENAME_SIZE];
    char alphamap[MAX_TEXTURE_FILENAME_SIZE];
	unsigned int id;
	std::vector<char> comment;
};

struct ms3d_keyframe
{
	float time;
	float key[3];
};

struct ms3d_tangent
{
	float tangentIn[3];
	float tangentOut[3];
};

struct ms3d_joint
{
	unsigned char flags;
	char name[32];
	char parentName[32];

	float rot[3];
	float pos[3];

	std::vector<ms3d_keyframe> rotationKeys;
	std::vector<ms3d_keyframe> positionKeys;
	std::vector<ms3d_tangent> tangents;

	std::vector<char> comment;
	float color[3];
		
	// used for rendering
	
	int parentIndex;
	float matLocalSkeleton[3][4];
	float matGlobalSkeleton[3][4];

	float matLocal[3][4];
	float matGlobal[3][4];
};

class CMS3DModelLoader
{
protected:

	//------------------------------------------------------
	//---- store model info
	//------------------------------------------------------

	float		model_animationFps;
	float		model_currentTime;
	int			model_totalFrames;
	
	float		model_jointSize;
	int			model_transparencyMode;
	float		model_alphaRef;

	std::vector<ms3d_vertex> model_vertices;
	std::vector<ms3d_triangle> model_triangles;
	std::vector<ms3d_group> model_groups;
	std::vector<ms3d_material> model_materials;
	std::vector<ms3d_joint> model_joints;
	std::vector<char> model_comment;

	//------------------------------------------------------
	//---- model inclusive
	//------------------------------------------------------

	bool		isVertex;
	bool		isTriangle;
	bool		isGroup;
	bool		isMaterial;
	bool		isJoint;

	//------------------------------------------------------
	//---- for store vertices and joints original info
	//------------------------------------------------------

	GLfloat		*vertices_array;

	GLfloat		*joints_array;
	
	//------------------------------------------------------
	//---- 
	//------------------------------------------------------

	MSfloat		*group_joints_array;
	GLfloat		*color_joints_array;
	GLfloat		*p_color_joints_array;

	MSfloat		*group_vertices_array;
	GLfloat		*normals_array;
	GLfloat		*tex_coord_array;

	//------------------------------------------------------
	//----
	//------------------------------------------------------

	GLushort	*joints_indices;
	GLushort	*p_joints_indices;

	MSushort	*vertices_indices;
	
	//------------------------------------------------------
	//----
	//------------------------------------------------------

	GLushort	numVertices;
	GLushort	numTriangles;
	GLushort	numIndices;
	GLushort	numGroups;

	GLushort	*numGroupTriangles;
	GLuint		*numGroupIndices;

	GLushort	numMaterials;
	GLushort	numJoints;

	GLushort	numKeyFramesRot;
	GLushort	numKeyFramesPos;

	//------------------------------------------------------
	//---- textures
	//------------------------------------------------------

	int			*materialsIndex;
	
	//------------------------------------------------------
	//---- variable bones
	//------------------------------------------------------

	MSchar		*parent;

public:
	
	CMS3DModelLoader();
	~CMS3DModelLoader();
	void ModelClear();
	
	bool IsCorrectID(const char *id);
	bool IsCorrectVersion(const int version);
	bool InitModel(char *filename);

	void LoadModel();
	void SetupVertexArray();
	void SetupTextureArray();
	void SetupJointsArray();
	
	void SetupJoints();
	void SetupTangents();
	void SetFrame(float frame);
	void SetAnimationFPS(int fps);
	void EvaluateJoint(int index, float frame);
	vec3 TransformJoint(const GLfloat v[3], const GLfloat m[3][4] );
	vec3 TransformVertex(const ms3d_vertex *vertex) const;
	void FillJointIndicesAndWeights(const ms3d_vertex *vertex, int jointIndices[4], int jointWeights[4]) const;	

	int				GetNumberOfVertex();
	int				GetNumberOFGroups();
	int				GetNumberOfMaterials();
	int				GetNumberOfIndexInGroup(int index);
	int				GetNumberOfJoints();
	int				GetNumberOfTotalFrame();

	float			GetAnimationFPS();
	GLuint			GetTexturesArray(int index);
	GLfloat*		GetVerticesArray();
	GLfloat*		GetGroupVerticesArray(int index);
	GLfloat*		GetTexCoordArray();
	GLushort*		GetVerticesIndices(int index);
	ms3d_material*	GetMaterial(int index);
	int				GetTransparencyMode();
	float			GetAlphaRef();
	char			GetMaterialForGroup(int index);

	GLfloat*		GetJointsArray();
	GLfloat*		GetGroupJointsArray(int index);

	GLfloat*		GetColorJointsArray();
	GLfloat*		GetPColorJointsArray();

	GLushort*		GetJointsIndices();
	GLushort*		GetPJointsIndices();

	bool			GetIsVertex();
	bool			GetIsTriangle();
	bool			GetIsGroup();
	bool			GetIsMaterial();
	bool			GetIsJoint();
};