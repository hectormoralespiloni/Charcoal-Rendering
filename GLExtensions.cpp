
#include "GLExtensions.h"

//define global extensions objects
PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObject	= NULL;
PFNGLSHADERSOURCEARBPROC			glShaderSource			= NULL;
PFNGLCOMPILESHADERARBPROC			glCompileShader			= NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObject	= NULL;
PFNGLATTACHOBJECTARBPROC			glAttachObject			= NULL;
PFNGLLINKPROGRAMARBPROC				glLinkProgram			= NULL;
PFNGLUSEPROGRAMOBJECTARBPROC		glUseProgramObject		= NULL;
PFNGLGETATTRIBLOCATIONARBPROC		glGetAttribLocation		= NULL;
PFNGLGETUNIFORMLOCATIONARBPROC		glGetUniformLocation	= NULL;
PFNGLDELETEOBJECTARBPROC			glDeleteObject			= NULL;
PFNGLDETACHOBJECTARBPROC			glDetachObject			= NULL;
PFNGLUNIFORM1IARBPROC				glUniform1i				= NULL;
PFNGLUNIFORM2IARBPROC				glUniform2i				= NULL;
PFNGLUNIFORM3IARBPROC				glUniform3i				= NULL;
PFNGLUNIFORM4IARBPROC				glUniform4i				= NULL;
PFNGLUNIFORM1FARBPROC				glUniform1f				= NULL;
PFNGLUNIFORM2FARBPROC				glUniform2f				= NULL;
PFNGLUNIFORM3FARBPROC				glUniform3f				= NULL;
PFNGLUNIFORM4FARBPROC				glUniform4f				= NULL;
PFNGLACTIVETEXTUREARBPROC			glActiveTexture			= NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC	glGetObjectParameteriv	= NULL;
PFNGLGETINFOLOGARBPROC				glGetInfoLog			= NULL;
PFNGLVALIDATEPROGRAMARBPROC			glValidateProgram		= NULL;
PFNWGLCREATEPBUFFERARBPROC			wglCreatePbuffer		= NULL;
PFNWGLGETPBUFFERDCARBPROC			wglGetPbufferDC			= NULL;
PFNWGLRELEASEPBUFFERDCARBPROC		wglReleasePbufferDC		= NULL;
PFNWGLDESTROYPBUFFERARBPROC			wglDestroyPbuffer		= NULL;
PFNWGLBINDTEXIMAGEARBPROC			wglBindTexImage			= NULL;
PFNWGLRELEASETEXIMAGEARBPROC		wglReleaseTexImage		= NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormat	= NULL;

///----------------------------------------------------------------------------
///Initializes OpenGL extensions for Win32.
///----------------------------------------------------------------------------
void InitExtensions()
{
	glCreateShaderObject	= (PFNGLCREATESHADEROBJECTARBPROC)	wglGetProcAddress("glCreateShaderObjectARB");
	glShaderSource			= (PFNGLSHADERSOURCEARBPROC)		wglGetProcAddress("glShaderSourceARB");
	glCompileShader			= (PFNGLCOMPILESHADERARBPROC)		wglGetProcAddress("glCompileShaderARB");
	glCreateProgramObject	= (PFNGLCREATEPROGRAMOBJECTARBPROC) wglGetProcAddress("glCreateProgramObjectARB");
	glAttachObject			= (PFNGLATTACHOBJECTARBPROC)		wglGetProcAddress("glAttachObjectARB");
	glLinkProgram			= (PFNGLLINKPROGRAMARBPROC)			wglGetProcAddress("glLinkProgramARB");
	glUseProgramObject		= (PFNGLUSEPROGRAMOBJECTARBPROC)	wglGetProcAddress("glUseProgramObjectARB");
	glGetAttribLocation		= (PFNGLGETATTRIBLOCATIONARBPROC)	wglGetProcAddress("glGetAttribLocationARB");
	glGetUniformLocation	= (PFNGLGETUNIFORMLOCATIONARBPROC)	wglGetProcAddress("glGetUniformLocationARB");
	glDeleteObject			= (PFNGLDELETEOBJECTARBPROC)		wglGetProcAddress("glDeleteObjectARB");
	glDetachObject			= (PFNGLDETACHOBJECTARBPROC)		wglGetProcAddress("glDetachObjectARB");
	glUniform1i				= (PFNGLUNIFORM1IARBPROC)			wglGetProcAddress("glUniform1iARB");
	glUniform2i				= (PFNGLUNIFORM2IARBPROC)			wglGetProcAddress("glUniform2iARB");
	glUniform3i				= (PFNGLUNIFORM3IARBPROC)			wglGetProcAddress("glUniform3iARB");
	glUniform4i				= (PFNGLUNIFORM4IARBPROC)			wglGetProcAddress("glUniform4iARB");
	glUniform1f				= (PFNGLUNIFORM1FARBPROC)			wglGetProcAddress("glUniform1fARB");
	glUniform2f				= (PFNGLUNIFORM2FARBPROC)			wglGetProcAddress("glUniform2fARB");
	glUniform3f				= (PFNGLUNIFORM3FARBPROC)			wglGetProcAddress("glUniform3fARB");
	glUniform4f				= (PFNGLUNIFORM4FARBPROC)			wglGetProcAddress("glUniform4fARB");
	glActiveTexture			= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glGetObjectParameteriv	= (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
	glGetInfoLog			= (PFNGLGETINFOLOGARBPROC)			wglGetProcAddress("glGetInfoLogARB");
	glValidateProgram		= (PFNGLVALIDATEPROGRAMARBPROC)		wglGetProcAddress("glValidateProgramARB");
	wglCreatePbuffer		= (PFNWGLCREATEPBUFFERARBPROC)		wglGetProcAddress("wglCreatePbufferARB");
	wglGetPbufferDC			= (PFNWGLGETPBUFFERDCARBPROC)		wglGetProcAddress("wglGetPbufferDCARB");
	wglReleasePbufferDC		= (PFNWGLRELEASEPBUFFERDCARBPROC)	wglGetProcAddress("wglReleasePbufferDCARB");
	wglDestroyPbuffer		= (PFNWGLDESTROYPBUFFERARBPROC)		wglGetProcAddress("wglDestroyPbufferARB");
	wglBindTexImage			= (PFNWGLBINDTEXIMAGEARBPROC)		wglGetProcAddress("wglBindTexImageARB");
	wglReleaseTexImage		= (PFNWGLRELEASETEXIMAGEARBPROC)	wglGetProcAddress("wglReleaseTexImageARB");
	wglChoosePixelFormat	= (PFNWGLCHOOSEPIXELFORMATARBPROC)	wglGetProcAddress("wglChoosePixelFormatARB");
}
