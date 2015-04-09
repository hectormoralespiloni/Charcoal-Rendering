///============================================================================
///@file	Geometry.h
///@brief	Class used for rendering the geometry in the scene.
///
///@author	Héctor Morales Piloni
///@date	November 18, 2006
///============================================================================

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include "GLExtensions.h"
#include "MilkshapeModel.h"
#include "ltga.h"

using namespace std;

class Geometry
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	Geometry();

	//-------------------------------------------------------------------------
	//Public methods
	//-------------------------------------------------------------------------
	void Draw(GLfloat angleX, GLfloat angleY);
	void SetLights(GLfloat pos[]);
	void SetMaterials();
	void SetTextures();
	void SetCameraPosition(GLfloat pos[]);
	void GetCameraPosition(GLfloat *pos) const;
	void GetLightPosition(GLfloat *pos) const;
	GLuint GetTexObj(int obj) const;

private:
	//-------------------------------------------------------------------------
	//Private members
	//-------------------------------------------------------------------------
	GLuint	m_Textures[3];	///> Array of textures 
	GLfloat m_Light[3];		///> Light's position
	GLfloat m_Camera[3];	///> Camera's position
	Model	*m_Model;		///> Milkshape3D mesh
};

#endif
