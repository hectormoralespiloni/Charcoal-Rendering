///============================================================================
///@file	ShaderProgram.cpp
///@brief	Shader Program Class Implementation
///
///@author	Héctor Morales Piloni
///@date	December 3, 2006
///============================================================================

#include "ShaderProgram.h"

///----------------------------------------------------------------------------
///Default constructor.
///----------------------------------------------------------------------------
ShaderProgram::ShaderProgram()
{
	m_Program = NULL;
}

///----------------------------------------------------------------------------
///Default destructor.
///----------------------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
	DestroyShader();
}

///----------------------------------------------------------------------------
///Enables the shader program object.
///----------------------------------------------------------------------------
void ShaderProgram::EnableShader()
{
	glUseProgramObject(m_Program);
}

///----------------------------------------------------------------------------
///Disables the shader program object.
///----------------------------------------------------------------------------
void ShaderProgram::DisableShader()
{
	glUseProgramObject(0);
}

///----------------------------------------------------------------------------
///Creates a shader program object.
///----------------------------------------------------------------------------
void ShaderProgram::CreateShader()
{
	m_Program = glCreateProgramObject();
}

///----------------------------------------------------------------------------
///"insert" shader into program object.
///@param obj	a ShaderObject pointer
///----------------------------------------------------------------------------
void ShaderProgram::AttachObject(ShaderObject *obj)
{
	glAttachObject(m_Program, obj->GetHandle());
}

///----------------------------------------------------------------------------
///Link program object and leave it ready to use
///----------------------------------------------------------------------------
void ShaderProgram::Link()
{
	glLinkProgram(m_Program);
}

///----------------------------------------------------------------------------
///Deletes shader program
///----------------------------------------------------------------------------
void ShaderProgram::DestroyShader()
{
	//objects attached to this program will be flagged for deletion
	glUseProgramObject(0);
	glDeleteObject(m_Program);
}

///----------------------------------------------------------------------------
///Sets a shader uniform int variable
///@param	uniformName - the name of the uniform variable
///@param	value - value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLint value)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform1i(location, value);
}

///----------------------------------------------------------------------------
///Sets a shader uniform int variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLint v1, GLint v2)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform2i(location, v1, v2);
}

///----------------------------------------------------------------------------
///Sets a shader uniform int variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///@param	v3 - third value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLint v1, GLint v2, GLint v3)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform3i(location, v1, v2, v3);
}

///----------------------------------------------------------------------------
///Sets a shader uniform int variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///@param	v3 - third value to be passed to the uniform variable
///@param	v4 - fourth value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLint v1, GLint v2, GLint v3, GLint v4)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform4i(location, v1, v2, v3, v4);
}

///----------------------------------------------------------------------------
///Sets a shader uniform float variable
///@param	uniformName - the name of the uniform variable
///@param	value - first value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLfloat value)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform1f(location, value);
}

///----------------------------------------------------------------------------
///Sets a shader uniform vec2 variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLfloat v1, GLfloat v2)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform2f(location, v1, v2);
}

///----------------------------------------------------------------------------
///Sets a shader uniform vec3 variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///@param	v3 - third value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLfloat v1, GLfloat v2, GLfloat v3)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform3f(location, v1, v2, v3);
}

///----------------------------------------------------------------------------
///Sets a shader uniform vec4 variable
///@param	uniformName - the name of the uniform variable
///@param	v1 - first value to be passed to the uniform variable
///@param	v2 - second value to be passed to the uniform variable
///@param	v3 - third value to be passed to the uniform variable
///@param	v4 - fourth value to be passed to the uniform variable
///----------------------------------------------------------------------------
void ShaderProgram::SetUniform(const GLcharARB *uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4)
{
	int location = glGetUniformLocation(m_Program, uniformName);
	glUniform4f(location, v1, v2, v3, v4);
}

///----------------------------------------------------------------------------
///Gets the info log for the current shader program
///@return	a string with the log
///----------------------------------------------------------------------------
/*
GLcharARB* ShaderProgram::GetLog() const
{
	int compiled;
	int length;
	int charsRead;
	GLcharARB *logStr;

	compiled = length = charsRead = 0;
	glValidateProgram(m_Shader);
	glGetObjectParameteriv(m_Shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
	logStr = (GLcharARB*)malloc(length*sizeof(GLcharARB));
	glGetInfoLog(m_Shader, length, &charsRead, logStr);

	return logStr;
}
*/