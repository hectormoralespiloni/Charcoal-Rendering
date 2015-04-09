
#ifndef GLEXTENSIONS_H
#define GLEXTENSIONS_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

//-------------------------------------------------------------------------
// Since Windows include only OpenGL version 1.1 support in opengl32.dll
// and the opengl32.lib stub library also contains only version 1.1 symbols,
// we must define entry-point functions for GL >= 1.2
//-------------------------------------------------------------------------
extern PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObject;
extern PFNGLSHADERSOURCEARBPROC				glShaderSource;
extern PFNGLCOMPILESHADERARBPROC			glCompileShader;
extern PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObject;
extern PFNGLATTACHOBJECTARBPROC				glAttachObject;
extern PFNGLLINKPROGRAMARBPROC				glLinkProgram;
extern PFNGLUSEPROGRAMOBJECTARBPROC			glUseProgramObject;
extern PFNGLGETATTRIBLOCATIONARBPROC		glGetAttribLocation;
extern PFNGLGETUNIFORMLOCATIONARBPROC		glGetUniformLocation;
extern PFNGLDELETEOBJECTARBPROC				glDeleteObject;
extern PFNGLDETACHOBJECTARBPROC				glDetachObject;
extern PFNGLUNIFORM1IARBPROC				glUniform1i;
extern PFNGLUNIFORM2IARBPROC				glUniform2i;
extern PFNGLUNIFORM3IARBPROC				glUniform3i;
extern PFNGLUNIFORM4IARBPROC				glUniform4i;
extern PFNGLUNIFORM1FARBPROC				glUniform1f;
extern PFNGLUNIFORM2FARBPROC				glUniform2f;
extern PFNGLUNIFORM3FARBPROC				glUniform3f;
extern PFNGLUNIFORM4FARBPROC				glUniform4f;
extern PFNGLACTIVETEXTUREARBPROC			glActiveTexture;
extern PFNGLGETOBJECTPARAMETERIVARBPROC		glGetObjectParameteriv;
extern PFNGLGETINFOLOGARBPROC				glGetInfoLog;
extern PFNGLVALIDATEPROGRAMARBPROC			glValidateProgram;
extern PFNWGLCREATEPBUFFERARBPROC			wglCreatePbuffer;
extern PFNWGLGETPBUFFERDCARBPROC			wglGetPbufferDC;
extern PFNWGLRELEASEPBUFFERDCARBPROC		wglReleasePbufferDC;
extern PFNWGLDESTROYPBUFFERARBPROC			wglDestroyPbuffer;
extern PFNWGLBINDTEXIMAGEARBPROC			wglBindTexImage;
extern PFNWGLRELEASETEXIMAGEARBPROC			wglReleaseTexImage;
extern PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormat;

void InitExtensions();

#endif
