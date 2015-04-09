//
//@file	charcoal.frag
//@brief	Real-Time charcoal rendering implementation fragment shader
//
//@author	Héctor Morales Piloni
//@date	December 29, 2006
//

uniform sampler2D noiseTex;	//noise texture
uniform sampler2D paperTex;	//paper texture
uniform sampler2D CET;		//pre-computed contrast enhanced texture

varying vec2 paperCoord;	//paper texture coordinates
varying vec2 noiseCoord;	//noise texture coordinates
varying vec3 N;				//normal vector
varying vec3 L;				//light vector
varying float ambient;		//ambient light's component

//----------------------------------------
//Computes the lambertian intensity
//and applies a contrast operator.
//@param N - normal vector from VS
//@param L - light vector from VS
//@param A - Ambient light intensity
//@return the computed CEO
//----------------------------------------
float CEO(vec3 N, vec3 L, float A)
{
	//normalize normal and light vectors
	N = normalize(N);
	L = normalize(L);
	
	//compute lambertian intensity
	float LI = max(0.0, dot(N, L));
	
	//add light ambient component to lambertian intensity
	LI = clamp(LI + A, 0.0, 1.0);
	
	//oversaturate to enhance the closure effect
	LI = clamp(LI * 1.5, 0.0, 1.0);
	
	//apply the contrast enhancement operator
	float contrast = pow(LI, 3.5);
	
	return contrast;
}

void main()
{
	//get a random color [0,1]
	vec4 rand = texture2D(noiseTex, noiseCoord);

	//compute the Contrast Enhancement Operator (CEO)
	float diffuseColor = CEO(N, L, ambient);

	//compute the Contrast Enhancement Texture (CET) coordinates	
	vec2 CETcoord = vec2(0.0, diffuseColor);
	
	//scale texture access from being too far apart
	//this prevents the noise texture from showing up
	CETcoord.s = rand.x * 0.5;
	CETcoord.t *= 0.5;
	
	//get the CET color
	vec4 CETColor = texture2D(CET, CETcoord);
	
	//blend CET with CEM
	vec4 smudgedColor = (diffuseColor + CETColor) * 0.5;

	//get paper texture color
	//invert the color so a simple vector addition overlay the paper texture onto CEM
	vec4 bumpVec = 1.0 - texture2D(paperTex, paperCoord);
	
	gl_FragColor = smudgedColor - bumpVec ;
}
