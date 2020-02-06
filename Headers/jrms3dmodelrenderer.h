#pragma once

#include"../Headers/jrms3dmodelloader.h"
#include"../Headers/jrtexteditor.h"

class CMS3DModelRenderer
{
private:
	CMS3DModelLoader *model_loader;
	bool render_joint;
public:

	CMS3DModelRenderer(CMS3DModelLoader *mdl);
	~CMS3DModelRenderer();

	void ToggleRenderJoint();
	
	void BindMaterial(int materialIndex);
	void TearMaterial();

	void DrawTexturedModel(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
	void DrawTexturedModel(const GLfloat &x, const GLfloat &y, const GLfloat &z, const int &f) const;

	void DrawModel();
	void DrawModel(const vec3 &pos, const vec3 &rot);
	void DrawAnimateModel(const vec3 &pos, const vec3 &rot, const int &f);

	void DrawJoints(const vec3 &pos, const vec3 &rot, const int f) const;
	void DrawJoints(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
	void DrawJoints(const GLfloat &x, const GLfloat &y, const GLfloat &z, const int frm) const;

	void PrintText(const vec3 &position, const vec3 &rot, char *text); 
};