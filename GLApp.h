///============================================================================
///@file	GLApp.h
///@brief	Defines the Main OpenGL application class.
///			This class inherits from Application abstract class which
///			takes care of the windows creation and main render loop
///
///@author	Héctor Morales Piloni
///@date	November 13, 2006
///============================================================================

#ifndef GLAPP_H
#define GLAPP_H

#include "GraphicsApp.h"
#include "Geometry.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "ShaderObject.h"
#include "GLExtensions.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/wglext.h>

class GLApp : public GraphicsApp
{
public:
	//-------------------------------------------------------------------------
	//Constructors and destructors
	//-------------------------------------------------------------------------
	GLApp();
	GLApp(LPSTR windowTitle, USHORT width, USHORT height);
	virtual ~GLApp();

	//-------------------------------------------------------------------------
	//Public methods
	//-------------------------------------------------------------------------
	virtual void InitGraphics();
	virtual void Render();
	virtual void RenderText(LPTSTR text);
	virtual bool ShutDown();
	virtual LRESULT DisplayWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
	//-------------------------------------------------------------------------
	//Private methods
	//-------------------------------------------------------------------------
	void Reshape(int w,int h);
	void Zoom(GLfloat zoomFactor);

	//-------------------------------------------------------------------------
	//Private members
	//-------------------------------------------------------------------------
	HGLRC			m_hRC;		///> Handle to OpenGL Rendering Context
	Geometry		m_Geometry;	///> Used to draw all the geometry in the scene
	Timer			m_Timer;	///> GL Application timer
	ShaderProgram	m_Shader;	///> A Shader program object
	GLdouble		m_CameraProjectionMatrix[16];	///> Camera projection matrix
	GLdouble		m_CameraViewMatrix[16];			///> Camera model-view matrix
	GLfloat			m_SpinX;
	GLfloat			m_SpinY;
};

#endif