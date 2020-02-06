#pragma once

#include"../Headers/jrmaprenderer.h"

CMapRenderer :: CMapRenderer(CMapLoader *ldr)
{
	map_loader	=	ldr;
}

CMapRenderer :: ~CMapRenderer()
{
	delete[] map_loader;
}

void CMapRenderer :: BindMaterial(int materialIndex)
{
	if (materialIndex < 0 || materialIndex >= map_loader->GetNumberOfMaterials())
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
		ms3d_material *material = map_loader->GetMaterial(materialIndex);
		glEnable(GL_TEXTURE_2D);

		if (material->transparency < 1.0f || material->mode & HASALPHA)
        {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, material->transparency);
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

			if (map_loader->GetTransparencyMode() == TRANSPARENCY_MODE_SIMPLE)
			{
				glDepthMask(GL_FALSE);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.0f);
			}
			else if (map_loader->GetTransparencyMode() == TRANSPARENCY_MODE_ALPHAREF)
			{
				glDepthMask(GL_TRUE);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, map_loader->GetAlphaRef());
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

void CMapRenderer :: TearMaterial()
{
	glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

	glDepthMask(GL_TRUE);
	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, map_loader->GetAlphaRef());
		
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void CMapRenderer :: DrawMap()
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
		

	glPushMatrix();
		
	for(int i = 0; i < map_loader->GetNumberOFGroups(); i++)
	{
		BindMaterial(map_loader->GetMaterialForGroup(i));
		glVertexPointer( 3, GL_FLOAT, 0, map_loader->GetVerticesArray());
		glTexCoordPointer( 2, GL_FLOAT, 0, map_loader->GetTexCoordArray());
		glDrawElements( GL_TRIANGLES, map_loader->GetNumberOfIndexInGroup(i), GL_UNSIGNED_SHORT, map_loader->GetVerticesIndices(i));
		TearMaterial();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}