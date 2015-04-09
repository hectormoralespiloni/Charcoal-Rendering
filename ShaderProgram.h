///============================================================================
///@file	ShaderProgram.h
///@brief	Shader Program class.
///
///@author	Héctor Morales Piloni
///@date	December 3, 2006
///============================================================================

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include "ShaderObject.h"
#include "GLExtensions.h"

class ShaderProgram
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	ShaderProgram();
	~ShaderProgram();

	//-------------------------------------------------------------------------
	//Public Methods
	//-------------------------------------------------------------------------
	void EnableShader();
	void DisableShader();
	void CreateShader();
	void DestroyShader();
	void AttachObject(ShaderObject* obj);
	void Link();
	void SetUniform(const GLcharARB* uniformName, GLint value);
	void SetUniform(const GLcharARB* uniformName, GLint v1, GLint v2);
	void SetUniform(const GLcharARB* uniformName, GLint v1, GLint v2, GLint v3);
	void SetUniform(const GLcharARB* uniformName, GLint v1, GLint v2, GLint v3, GLint v4);
	void SetUniform(const GLcharARB* uniformName, GLfloat value);
	void SetUniform(const GLcharARB* uniformName, GLfloat v1, GLfloat v2);
	void SetUniform(const GLcharARB* uniformName, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform(const GLcharARB* uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
	//GLcharARB* GetLog() const;

protected:
	//-------------------------------------------------------------------------
	//Private Members
	//-------------------------------------------------------------------------
	ShaderObject *m_Shaders;	///> Attachable shader objects (i.e. Vertex/Fragment shaders)
	GLhandleARB m_Program;		///> Handle to Shader program
};

#endif
