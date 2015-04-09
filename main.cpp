///============================================================================
///@file	main.cpp
///@brief	Charcoal Rendering.
///			Implementation of the Real-time hardware accelerated Charcoal
///			Rendering algorithm by Aditi Majumder & M. Gopi
///
///@author	Héctor Morales Piloni
///@date	December 22, 2006
///============================================================================

#include <windows.h>
#include "GLApp.h"

GLApp *myApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
	int retCode;

	//create a new 512x512 window application
	myApp = new GLApp("Charcoal Rendering Demo", 512, 512);
	
	//initilize the application
	if(!myApp->InitInstance(hInstance, lpCmdLine, iCmdShow)) 
	{
		delete myApp;
		return 0;
	}

	//start the application
	retCode = myApp->StartApp();

	//clean-up
	delete myApp;

	return retCode;
}