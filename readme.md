CHARCOAL RENDERING GLSL (Jan-2007)
----------------------------------

![](https://github.com/hectormoralespiloni/Charcoal-Rendering/blob/master/charcoal_full.jpg)

1. SUMMARY 
	This is an implementation of the Real-time hardware accelerated 
	Charcoal Rendering algorithm by Aditi Majumder & M. Gopi 
	using OpenGL and shaders with GLSL.

2. REQUIREMENTS TO RUN THE EXE
	* OpenGL runtimes installed (glu32.dll, glut32.dll)
	* Vertex & Pixel programmable graphic card
	
3. HOW TO PLAY THE DEMO
	* Right mouse click => Zoom the camera
	* Left mouse click  => Rotates the model
	
4. HOW TO COMPILE
	In order to compile this demo you will need:
	* Microsoft Visual Studio 2005.

	* Microsoft Platform SDK (only needed if using VS Express Edition).
 	In order to setup Visual C++ 2005 Express Edition with the Microsoft 
 	platform SDK you probably need to read this: 
 	http://msdn.microsoft.com/vstudio/express/visualc/usingpsdk/

	* glext.h & wglext.h header files for OpenGL extensions (included)

	* Microsoft Windows OpenGL 1.2+ libraries for linking (glu32.lib).
 	This should be already present in your VS installation.

	* OpenGL Utility Toolkit (GLUT) for Win32 which can be dowloaded from: 
 	http://www.xmission.com/~nate/glut.html

5. CODE STURCTURE
	* The main program creates and starts an instance of a GLApp which 
	inherits from the abstract class GraphicsApp (which is used in 
	other of my demos either with OpenGL or DX).

	* "GraphicsApp" creates the main windows application loop and the 
	window display (i.e. the basic windows stuff).
 
	* "GLApp" takes care of processing the messages, initialize the OpenGL
	engine and render the demo model with shaders.

	* "Geometry" class methods are called from GLApp and they take care
	or rendering the actual milkshape model, set lights and cameras and
	materials. 

	* "Timer" class by Adam Hoult which handles all timing functionality 
	such as counting the number of frames per second, etc.	

	* "Extensions" is a wrapper class which loasd  the required GL extensions
	for windows (WGL)

	* "ShaderObject" and "ShaderProgram" are wrapper classes to handle all the 
	required steps setting up GLSL shaders (which can be cumbersome).

	* This demo uses shaders: CharcoalRendering.frag and CharcoalRendering.frag
	for vertex & fragment shaders respectively.