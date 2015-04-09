//
//@file	charcoal.vert
//@brief	Real-Time charcoal rendering implementation vertex shader
//
//@author	Héctor Morales Piloni
//@date	December 29, 2006
//

varying vec2 paperCoord;	//paper texture coordinates
varying vec2 noiseCoord;	//noise texture coordinates
varying vec3 N;				//normal vector
varying vec3 L;				//light vector
varying float ambient;		//ambient light's component

void main()
{	
	//transform vertices
	gl_Position = ftransform();
		
	//compute vertex normals
	N = gl_NormalMatrix * gl_Normal;
	
	//compute light vector
	L = gl_LightSource[0].position.xyz - gl_Vertex.xyz;

	//get light's ambient component
	ambient = gl_LightSource[0].ambient.r;
	
	//compute paper texture coordinates to be in [0,1] range
	paperCoord.st = (gl_Position.xy / gl_Position.w) * 0.5 + 0.5;
	
	//compute noise texture coordinates
	noiseCoord.st = gl_Position.xy;
}
