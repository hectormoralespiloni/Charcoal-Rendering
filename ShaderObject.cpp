///============================================================================
///@file	ShaderObject.cpp
///@brief	Shader Object Class Implementation
///
///@author	Héctor Morales Piloni
///@date	December 6, 2006
///============================================================================

#include "ShaderObject.h"

///----------------------------------------------------------------------------
///Default constructor.
///----------------------------------------------------------------------------
ShaderObject::ShaderObject(LPSTR fileName, GLenum shaderType)
{
	CreateShader(fileName, shaderType);
}

///----------------------------------------------------------------------------
///Default destructor.
///----------------------------------------------------------------------------
ShaderObject::~ShaderObject()
{
	glDeleteObject(m_Shader);
}

///----------------------------------------------------------------------------
///Get handle to shader object.
///@return the object handle
///----------------------------------------------------------------------------
GLhandleARB ShaderObject::GetHandle() const
{
	return m_Shader;
}

///----------------------------------------------------------------------------
///Loads a shader program from an external file into the specified buffer
///@param	fileName - the name of the shader program to load
///@return	a pointer to the buffer that receives the data read
///----------------------------------------------------------------------------
string ShaderObject::LoadShaderFromFile(LPSTR fileName)
{
	string line;
	string buffer;

	//load the file
    ifstream file(fileName);

	//read each line
    while(getline(file, line))
        buffer += line + "\n";

	return buffer;

	/* FANCY STUFF THAT DIDN'T WORK AT ALL... BECAUSE OF THE NULL TERMINATED ISSUE
	HANDLE hFile;
	DWORD fileSize;
	DWORD bytesRead;
	LPVOID pBuffer;

	//open the existing file
	hFile = CreateFile(fileName,				//the name of the file to open
					   GENERIC_READ,			//the access to the object (can be RW, WR or both)
					   0,						//share mode (zero for no sharing)
					   NULL,					//security attributes
					   OPEN_EXISTING,			//action to take on files
					   FILE_ATTRIBUTE_NORMAL,	//attributes and flags
					   NULL);					//handle to template

	//get file size
	fileSize = GetFileSize(hFile, NULL);

	//save memory space for buffer
	pBuffer = malloc(fileSize * sizeof(GLcharARB));

	//read file into specified buffer
	ReadFile(hFile, pBuffer, fileSize, &bytesRead, NULL);

	//close file handle
	CloseHandle(hFile);

	return (GLcharARB*)pBuffer;
	*/
}

///----------------------------------------------------------------------------
///Create, load, compile & link a shader object
///@param	fileName - the name of the shader source file
///----------------------------------------------------------------------------
void ShaderObject::CreateShader(LPSTR fileName, GLenum shaderType)
{
	GLcharARB *shaderSrc = NULL;
	string str;

	//load shader from file
	str = LoadShaderFromFile(fileName);

	//convert the contents of a string as a C-style, null-terminated string
	shaderSrc = (GLcharARB *) str.c_str();

	//create shader object
	m_Shader = glCreateShaderObject(shaderType);

	//set shader program source
	glShaderSource(m_Shader, 1, (const GLchar**)&shaderSrc, NULL);

	//free our temporal buffer
	free(shaderSrc);

	//compile shader
	glCompileShader(m_Shader);
}
