///============================================================================
///@file	Geometry.cpp
///@brief	Class used for rendering the geometry in the scene.
///
///@author	Héctor Morales Piloni
///@date	November 18, 2006
///============================================================================

#include "Geometry.h"

///----------------------------------------------------------------------------
///Default constructor
///----------------------------------------------------------------------------
Geometry::Geometry()
{
	m_Model = new MilkshapeModel();
	m_Model->loadModelData( "textures\\model.ms3d" );
}

///----------------------------------------------------------------------------
///Draw the objects in the scene
///@param	angle - used to animate part of the geometry
///----------------------------------------------------------------------------
void Geometry::Draw(GLfloat angleX, GLfloat angleY)
{
	glRotatef(angleY, 1.0, 0.0, 0.0);
	glRotatef(-angleX, 0.0, 1.0, 0.0);
	m_Model->draw();
}

///----------------------------------------------------------------------------
///Set the lights in the scene
///----------------------------------------------------------------------------
void Geometry::SetLights(GLfloat pos[])
{
	//define the light position
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	//enable lighting and light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

///----------------------------------------------------------------------------
///Set the materials of the objects in the scene
///----------------------------------------------------------------------------
void Geometry::SetMaterials()
{
	GLfloat white[4] = {1.0, 1.0, 1.0};

	//set object color as material color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//enable color material state
	glEnable(GL_COLOR_MATERIAL);

	//enable specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.f);
}

///----------------------------------------------------------------------------
///Sets the camera position.
///@param	pos[] - the camera position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::SetCameraPosition(GLfloat pos[])
{
	m_Camera[0] = pos[0];
	m_Camera[1] = pos[1];
	m_Camera[2] = pos[2];
}

///----------------------------------------------------------------------------
///Gets the camera position.
///@param	pos[] - the returned camera position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::GetCameraPosition(GLfloat *pos) const
{
	pos[0] = m_Camera[0];
	pos[1] = m_Camera[1];
	pos[2] = m_Camera[2];
}

///----------------------------------------------------------------------------
///Gets the light position.
///@param	pos[] - the returned light position (x,y,z)
///----------------------------------------------------------------------------
void Geometry::GetLightPosition(GLfloat *pos) const
{
	pos[0] = m_Light[0];
	pos[1] = m_Light[1];
	pos[2] = m_Light[2];
}

///----------------------------------------------------------------------------
///Set textures for shadow maps
///----------------------------------------------------------------------------
void Geometry::SetTextures()
{
	//generate the texture names
	glGenTextures(3, m_Textures);

	LTGA noise("textures\\noise.tga");
	LTGA contrast("textures\\contrast.tga");
	LTGA paper("textures\\paper.tga");

	//set paper texture
	glBindTexture(GL_TEXTURE_2D, m_Textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,		//target must be GL_TEXTURE_2D
				 0,					//LOD number
				 GL_RGB,			//number of color components
				 512,				//width
				 512,				//height
				 0,					//border
				 GL_RGB,			//format of pixel data
				 GL_UNSIGNED_BYTE,	//type of pixel data
				 paper.GetPixels());//pointer to image data in memory

	//set noise texture
	glBindTexture(GL_TEXTURE_2D, m_Textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,	
				 0,					
				 GL_RGB,			
				 256,				
				 256,				
				 0,					
				 GL_RGB,			
				 GL_UNSIGNED_BYTE,	
				 noise.GetPixels());

	//set contrast texture
	glBindTexture(GL_TEXTURE_2D, m_Textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,		
				 0,					
				 GL_RGB,			
				 256,				
				 256,				
				 0,					
				 GL_RGB,			
				 GL_UNSIGNED_BYTE,	
				 contrast.GetPixels());


}

///----------------------------------------------------------------------------
///GetTextObj()
///@param	int obj the textured object requested
///@returns the requested texture objectID
///----------------------------------------------------------------------------
GLuint Geometry::GetTexObj(int obj) const
{
	return m_Textures[obj];
}