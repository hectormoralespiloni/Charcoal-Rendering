///============================================================================
///@file	ShaderObject.h
///@brief	Shader Object class.
///
///@author	Héctor Morales Piloni
///@date	December 6, 2006
///============================================================================

#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include "GLExtensions.h"

using namespace std;

class ShaderObject
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	ShaderObject(LPSTR fileName, GLenum shaderType);
	~ShaderObject();

	//-------------------------------------------------------------------------
	//Public methods
	//-------------------------------------------------------------------------
	GLhandleARB GetHandle() const;

private:
	//-------------------------------------------------------------------------
	//Private methods
	//-------------------------------------------------------------------------
	void CreateShader(LPSTR fileName, GLenum shaderType);
	string LoadShaderFromFile(LPSTR fileName);

	//-------------------------------------------------------------------------
	//Private members
	//-------------------------------------------------------------------------
	GLhandleARB m_Shader;	///> Handle to Shader objects
};

#endif
