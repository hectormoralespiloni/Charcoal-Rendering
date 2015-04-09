///============================================================================
///@file	GLApp.cpp
///@brief	OpenGL Application Class Implementation
///
///@author	Héctor Morales Piloni
///@date	November 13, 2006
///============================================================================

#include "GLApp.h"

//Ok, these should be working as private members, don't know why they aren't
//so i didn't bother and make them globals... wtf?
GLboolean m_MousingR = false;
GLboolean m_MousingL = false;
POINT m_LastMousePos;
POINT m_CurrentMousePos;

///----------------------------------------------------------------------------
///Default constructor.
///----------------------------------------------------------------------------
GLApp::GLApp()
{
	//call overloaded constructor with default values
	GLApp("", 640, 480);
}

///----------------------------------------------------------------------------
///Overloaded constructor.
///@param	windowTitle - window title
///@param	width		- window width
///@param	height		- window height
///----------------------------------------------------------------------------
GLApp::GLApp(LPSTR windowTitle, USHORT width, USHORT height)
{
	//clear all required values
	m_hWnd	= NULL;
	m_hDC	= NULL;
	m_hRC	= NULL;

	//set all required values
	m_WindowTitle	= windowTitle;
	m_Width			= width;
	m_Height		= height;

	m_SpinX = 0.0f;
	m_SpinY = 0.0f;
}

///----------------------------------------------------------------------------
///Default destructor.
///----------------------------------------------------------------------------
GLApp::~GLApp()
{
	//perform clean-up
	ShutDown();
}

///----------------------------------------------------------------------------
///Initialize OpenGL graphic device context.
///----------------------------------------------------------------------------
void GLApp::InitGraphics()
{
	GLuint PixelFormat;			//this will hold the actual pixel format
	PIXELFORMATDESCRIPTOR pfd;	//structure to maintain pixel format information 
								//about our GL window

	//clear our PIXELFORMATDESCRIPTOR structure
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	//the size of this data structure
	pfd.nVersion = 1;							//this value should be set to 1!
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |			//the buffer can draw to a window or DC
				  PFD_SUPPORT_OPENGL |			//the buffer supports OpenGL drawing 
				  PFD_DOUBLEBUFFER;				//the buffer is double-buffered
	pfd.iPixelType = PFD_TYPE_RGBA;				//RGBA pixels
	pfd.cColorBits = 32;						//number of color bitplanes in each color buffer
	pfd.cDepthBits = 24;						//depth of the deph (z-axis) buffer

	//get the window device context
	m_hDC = GetDC(m_hWnd);

	//we should select a pixel format in the device 
	//context before calling wglCreateContext 
	PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, PixelFormat, &pfd);
	DescribePixelFormat(m_hDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	
	//creates a new OpenGL rendering context, which is 
	//suitable for drawing on the device referenced by m_hDC
	m_hRC = wglCreateContext(m_hDC);
	
	//set the current rendering context
	if(wglMakeCurrent(m_hDC, m_hRC) == FALSE)
	{
		MessageBox(NULL, 
				   "Could not set the current window context!", 
				   "ERROR", 
				   MB_OK | MB_ICONEXCLAMATION);

		//exit the program with an error code
		exit(-1);
	}

	//initialize the viewport
	Reshape(m_Width, m_Height);

	//set lights, materials & textures
	GLfloat lightPos[3] = {50.0, 90.0, 50.0};
	m_Geometry.SetLights(lightPos);
	m_Geometry.SetMaterials();

	//set camera position
	GLfloat cameraPos[3] = {5.0, 15.0, -85.0};
	m_Geometry.SetCameraPosition(cameraPos);

	//calculate & save matrices for later use, 
	//select modelview as temporal matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		//camera projection matrix
		glLoadIdentity();
		gluPerspective(45.0f, (float)m_Width/m_Height, 1.0f, 1000.0f);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_CameraProjectionMatrix);

		//camera modelview matrix
		glLoadIdentity();
		gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0.0f, 30.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);
	}
	glPopMatrix();

	//enable needed states
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//initialize OpenGL extensions
	InitExtensions();

	m_Geometry.SetTextures();

	//create vertex & pixel shaders
	m_Shader.CreateShader();
	m_Shader.AttachObject(new ShaderObject("CharcoalRendering.vert", GL_VERTEX_SHADER));
	m_Shader.AttachObject(new ShaderObject("CharcoalRendering.frag", GL_FRAGMENT_SHADER));
	m_Shader.Link();
}

///----------------------------------------------------------------------------
///Clean up resources.
///----------------------------------------------------------------------------
bool GLApp::ShutDown()
{
	//destroy shader program
	m_Shader.DestroyShader();

	if(m_hRC)
	{
		//make current rendering context NULL 
		wglMakeCurrent(NULL, NULL);
		
		//delete GL context
		wglDeleteContext(m_hRC);	
	}

	//release the device context
	if(m_hWnd && m_hDC) ReleaseDC(m_hWnd, m_hDC);

	//destroy window explicitly
	if(m_hWnd) DestroyWindow(m_hWnd);

	//reset all required values
	m_hDC = NULL;
	m_hRC = NULL;
	m_hWnd = NULL;

	return true;
}

///----------------------------------------------------------------------------
///This function handles messages for the GLApp object
///@param	hWnd - handle to window
///@param	Msg - the message sent
///@param	wParam - message parameter
///@param	lParam - message parameter
///----------------------------------------------------------------------------
LRESULT GLApp::DisplayWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GLfloat CameraPos[3];

	switch(Msg)
	{
		case WM_CREATE:
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_SIZE:
			//store new viewport sizes
			m_Width  = LOWORD(lParam);
			m_Height = HIWORD(lParam);

			Reshape(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_RBUTTONDOWN:
			m_LastMousePos.x = m_CurrentMousePos.x = LOWORD (lParam);
            m_LastMousePos.y = m_CurrentMousePos.y = HIWORD (lParam);
			m_MousingR = true;
			break;

		case WM_RBUTTONUP:
			m_MousingR = false;
			break;

		case WM_MOUSEMOVE:
			m_CurrentMousePos.x = LOWORD (lParam);
			m_CurrentMousePos.y = HIWORD (lParam);
			
			if(m_MousingR)
			{
				m_SpinX -= (m_CurrentMousePos.x - m_LastMousePos.x);
				m_SpinY -= (m_CurrentMousePos.y - m_LastMousePos.y);
			}

			if(m_MousingL)
				Zoom(m_CurrentMousePos.y - m_LastMousePos.y);

			m_LastMousePos.x = m_CurrentMousePos.x;
			m_LastMousePos.y = m_CurrentMousePos.y;
			break;

		case WM_LBUTTONDOWN:
			m_LastMousePos.x = m_CurrentMousePos.x = LOWORD (lParam);
            m_LastMousePos.y = m_CurrentMousePos.y = HIWORD (lParam);
			m_MousingL = true;
			break;

		case WM_LBUTTONUP:
			m_MousingL = false;
			break;

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}

///----------------------------------------------------------------------------
///Draws some text in the scene (i.e. FPS, etc)
///----------------------------------------------------------------------------
void GLApp::RenderText(LPTSTR text)
{
}

///----------------------------------------------------------------------------
///Overriden Render function (draws the scene).
///----------------------------------------------------------------------------
void GLApp::Render()
{
	//lock the framerate to 60 FPS
	m_Timer.Tick(60.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0, m_Width, m_Height);

	//draw the background paper texture
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -1.0, 1.0, -1.0, 1.0 );
    
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
	glBegin(GL_QUADS);
    {
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -1.0f, -1.0f, 0.0f );
    
        glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -1.0f, 1.0f, 0.0f );

        glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 1.0f, 1.0f, 0.0f );

        glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 1.0f, -1.0f, 0.0f );
    }
    glEnd();

	//clear depth buffer in order to render 3d model
	glClear(GL_DEPTH_BUFFER_BIT);

	//load view & projection matrices
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(m_CameraProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m_CameraViewMatrix);

	//bind textures that our shader will use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Geometry.GetTexObj(0));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Geometry.GetTexObj(1));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_Geometry.GetTexObj(2));

	//enable programmable pipeline
	m_Shader.EnableShader();
	
	//set uniform variables
	m_Shader.SetUniform("paperTex", 0);
	m_Shader.SetUniform("noise", 1);
	m_Shader.SetUniform("CET", 2);

	//and draw the model...
	m_Geometry.Draw(m_SpinX, m_SpinY);

	//disable programmable pipeline
	m_Shader.DisableShader();

	SwapBuffers(m_hDC);
}

///----------------------------------------------------------------------------
///Reset the viewport when window size changes
///@param	w - window width
///@param	h - window height
///----------------------------------------------------------------------------
void GLApp::Reshape(int w, int h)
{
	//set the viewport
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		//calculate the new projection matrix
		glLoadIdentity();
		gluPerspective(45.0f, (float)w/h, 1.0f, 1000.0f);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_CameraProjectionMatrix);
	}
	glPopMatrix();
}

///----------------------------------------------------------------------------
///Zoom in/out the camera
///@param	zoomFactor - how much zoom are we going to apply
///			if positive the camera gets closer to the scene,
///			if negative the camera gets further.
///----------------------------------------------------------------------------
void GLApp::Zoom(GLfloat zoomFactor)
{
	//set new camera position
	GLfloat cameraPos[3];
	
	m_Geometry.GetCameraPosition(cameraPos);
	//cameraPos[0] += zoomFactor;
	//cameraPos[1] += zoomFactor;
	cameraPos[2] += zoomFactor;
	m_Geometry.SetCameraPosition(cameraPos);

	//calculate the new modelview matrix
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0.0f, 30.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glGetDoublev(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);
}
