#pragma once

#include"../Headers/jrms3dmodelrenderer.h"

CMS3DModelRenderer :: CMS3DModelRenderer(CMS3DModelLoader *mdl)
{
	model_loader	=	mdl;
	render_joint	=	false;
}

CMS3DModelRenderer :: ~CMS3DModelRenderer()
{
	delete[] model_loader;
}

void CMS3DModelRenderer :: ToggleRenderJoint()
{
	if(render_joint		==	true)
	{
		render_joint	=	false;
	}
	else
	{
		render_joint	=	true;
	}
}

void CMS3DModelRenderer :: BindMaterial(int materialIndex)
{
	if (materialIndex < 0 || materialIndex >= model_loader->GetNumberOfMaterials())
	{
		glDepthMask(GL_TRUE);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glColor4f(1, 1, 1, 1);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, 0);
		float ma[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float md[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float ms[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float me[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mss = 0.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ma);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, md);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, me);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mss);		
	}
	else
	{
		ms3d_material *material = model_loader->GetMaterial(materialIndex);
		glEnable(GL_TEXTURE_2D);

		if (material->transparency < 1.0f || material->mode & HASALPHA)
        {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, material->transparency);
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

			if (model_loader->GetTransparencyMode() == TRANSPARENCY_MODE_SIMPLE)
			{
				glDepthMask(GL_FALSE);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.0f);
			}
			else if (model_loader->GetTransparencyMode() == TRANSPARENCY_MODE_ALPHAREF)
			{
				glDepthMask(GL_TRUE);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, model_loader->GetAlphaRef());
			}
        }
        else
        {
            glDisable(GL_BLEND);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        }
		
		if (material->mode & SPHEREMAP)
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		}
		else
		{
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		glBindTexture(GL_TEXTURE_2D, material->id);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material->emissive);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
	}
}

void CMS3DModelRenderer :: TearMaterial()
{
	glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

	glDepthMask(GL_TRUE);
	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, model_loader->GetAlphaRef());
		
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void CMS3DModelRenderer :: DrawTexturedModel(const GLfloat &x,const GLfloat &y,const GLfloat &z) const
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	glTranslated(x,y,z);

	for(int i = 0; i < model_loader->GetNumberOFGroups(); i++)
	{
		glBindTexture( GL_TEXTURE_2D, model_loader->GetTexturesArray(i));
		glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetVerticesArray());
		glTexCoordPointer( 2, GL_FLOAT, 0, model_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, model_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, model_loader->GetVerticesIndices(i));
	}
	glPopMatrix();
	
	if(render_joint)
	{
		DrawJoints(x,y,z);
	}
}

void CMS3DModelRenderer :: DrawTexturedModel(const GLfloat &x,const GLfloat &y,const GLfloat &z, const int &frm) const
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	glTranslated( x, y, z);

	for(int i=0;i<model_loader->GetNumberOFGroups();i++)
	{
		glBindTexture( GL_TEXTURE_2D, model_loader->GetTexturesArray(i));
		glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupVerticesArray(frm));
		glTexCoordPointer( 2, GL_FLOAT, 0, model_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, model_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, model_loader->GetVerticesIndices(i));
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	
	if(render_joint)
	{
		DrawJoints(x,y,z,frm);
	}
}

void CMS3DModelRenderer :: DrawModel()
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	for(int i=0;i<model_loader->GetNumberOFGroups();i++)
	{
		//glBindTexture( GL_TEXTURE_2D, model_loader->GetTexturesArray(i));
		BindMaterial(model_loader->GetMaterialForGroup(i));
		glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetVerticesArray());
		glTexCoordPointer( 2, GL_FLOAT, 0, model_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, model_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, model_loader->GetVerticesIndices(i));
		TearMaterial();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void CMS3DModelRenderer :: DrawModel(const vec3 &pos, const vec3 &rot)
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	glTranslated( pos.x, pos.y, pos.z);

	glRotatef(RadianToDegree(rot.x),1.0f,0.0f,0.0f);
	glRotatef(RadianToDegree(rot.y),0.0f,1.0f,0.0f);
	glRotatef(RadianToDegree(rot.z),0.0f,0.0f,1.0f);

	for(int i=0;i<model_loader->GetNumberOFGroups();i++)
	{
		//glBindTexture( GL_TEXTURE_2D, model_loader->GetTexturesArray(i));
		BindMaterial(model_loader->GetMaterialForGroup(i));
		glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetVerticesArray());
		glTexCoordPointer( 2, GL_FLOAT, 0, model_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, model_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, model_loader->GetVerticesIndices(i));
		TearMaterial();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void  CMS3DModelRenderer :: DrawAnimateModel(const vec3 &pos, const vec3 &rot, const int &f) 
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	glTranslated( pos.x, pos.y, pos.z);

	glRotatef(RadianToDegree(rot.x),1.0f,0.0f,0.0f);
	glRotatef(RadianToDegree(rot.y),0.0f,1.0f,0.0f);
	glRotatef(RadianToDegree(rot.z),0.0f,0.0f,1.0f);

	for(int i=0;i<model_loader->GetNumberOFGroups();i++)
	{
		BindMaterial(model_loader->GetMaterialForGroup(i));
		glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupVerticesArray(f));
		glTexCoordPointer( 2, GL_FLOAT, 0, model_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, model_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, model_loader->GetVerticesIndices(i));
		TearMaterial();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	if(render_joint && model_loader->GetIsJoint())
	{
		DrawJoints(pos, rot, f);
	}
}

void CMS3DModelRenderer :: DrawJoints(const vec3 &pos, const vec3 &rot, const int f) const
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glLineWidth(4);
	glPushMatrix();
		
	glTranslated( pos.x, pos.y, pos.z);

	glRotatef(RadianToDegree(rot.x),1.0f,0.0f,0.0f);
	glRotatef(RadianToDegree(rot.y),0.0f,1.0f,0.0f);
	glRotatef(RadianToDegree(rot.z),0.0f,0.0f,1.0f);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupJointsArray(f));
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetColorJointsArray() );
	glDrawElements( GL_LINES, (model_loader->GetNumberOfJoints() - 1) * 2, GL_UNSIGNED_SHORT, model_loader->GetJointsIndices());

	glPopMatrix();
	glLineWidth(1);

	//----------------------------

	glPointSize(4);
	glPushMatrix();
		
	glTranslated( pos.x, pos.y, pos.z);

	glRotatef(RadianToDegree(rot.x),1.0f,0.0f,0.0f);
	glRotatef(RadianToDegree(rot.y),0.0f,1.0f,0.0f);
	glRotatef(RadianToDegree(rot.z),0.0f,0.0f,1.0f);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupJointsArray(f) );
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetPColorJointsArray() );
	glDrawElements( GL_POINTS, model_loader->GetNumberOfJoints(), GL_UNSIGNED_SHORT, model_loader->GetPJointsIndices() );

	glPopMatrix();
	glPointSize(1);

	glEnable(GL_DEPTH_TEST);

}

void CMS3DModelRenderer :: DrawJoints(const GLfloat &x,const GLfloat &y,const GLfloat &z) const
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glLineWidth(4);
	glPushMatrix();
		
	glTranslated( x, y, z);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetJointsArray() );
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetColorJointsArray() );
	glDrawElements( GL_LINES, (model_loader->GetNumberOfJoints() - 1) * 2, GL_UNSIGNED_SHORT, model_loader->GetJointsIndices());

	glPopMatrix();
	glLineWidth(1);

	glPointSize(4);
	glPushMatrix();
		
	glTranslated( x, y, z);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetJointsArray() );
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetPColorJointsArray() );
	glDrawElements( GL_POINTS, model_loader->GetNumberOfJoints(), GL_UNSIGNED_SHORT, model_loader->GetPJointsIndices() );

	glPopMatrix();
	glPointSize(1);

	glEnable(GL_DEPTH_TEST);
}

void CMS3DModelRenderer :: DrawJoints(const GLfloat &x,const GLfloat &y,const GLfloat &z,const int frm) const
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glLineWidth(4);
	glPushMatrix();
		
	glTranslated(x,y,z);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupJointsArray(frm));
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetColorJointsArray());
	glDrawElements( GL_LINES, (model_loader->GetNumberOfJoints() - 1) * 2, GL_UNSIGNED_SHORT, model_loader->GetJointsIndices() );

	glPopMatrix();
	glLineWidth(1);

	glPointSize(4);
	glPushMatrix();
		
	glTranslated(x,y,z);

	glVertexPointer( 3, GL_FLOAT, 0, model_loader->GetGroupJointsArray(frm) );
	glColorPointer( 3, GL_FLOAT, 0, model_loader->GetPColorJointsArray() );
	glDrawElements( GL_POINTS, model_loader->GetNumberOfJoints(), GL_UNSIGNED_SHORT, model_loader->GetPJointsIndices() );

	glPopMatrix();
	glPointSize(1);

	//glDisableClientState(GL_COLOR_ARRAY);

	glEnable(GL_DEPTH_TEST);
}

void CMS3DModelRenderer :: PrintText(const vec3 &position, const vec3 &rot, char *text)
{
	glPushMatrix();

	glRotatef(rot.x, 1.0, 0, 0);
	glRotatef(rot.y, 0, 1.0, 0);
	glRotatef(rot.z, 0, 0, 1.0);

	CString :: PrintOnPlanX(position.x, position.y, position.z,GLUT_BITMAP_TIMES_ROMAN_24, text);

	glPopMatrix();
}