// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_Position;
in vec4 frag_Normal;
in vec4 frag_Light_Direction;

// Output from Fragment Shader
out vec4 pixel_Colour;

// Light Source
uniform vec4 Ia = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Material - Brass
uniform vec4 Ka = vec4(0.329412, 0.223529, 0.027451, 1.0);
uniform vec4 Kd = vec4(0.780392, 0.568627, 0.113725, 1.0);
uniform vec4 Ks = vec4(0.992157, 0.941176, 0.807843, 1.0);
uniform float a = 27.89743616;

// // Material - Pearl
// uniform vec4 Ka = vec4(0.25,     0.20725,  0.20725,  1.0);
// uniform vec4 Kd = vec4(1.0,      0.829,    0.82900,  1.0);
// uniform vec4 Ks = vec4(0.296648, 0.296648, 0.296648, 1.0);
// uniform float a = 11.264;

// // Material - Emerald
// uniform vec4 Ka = vec4(0.0215,  0.1745,   0.0215,  1.0f);
// uniform vec4 Kd = vec4(0.07568, 0.61424,  0.07568, 1.0f);
// uniform vec4 Ks = vec4(0.633,   0.727811, 0.633,   1.0f);
// uniform float a = 76.8;

// // Material - Turquoise
// uniform vec4 Ka = vec4(0.1,      0.18725, 0.1745,   1.0f);
// uniform vec4 Kd = vec4(0.396,    0.74151, 0.69102,  1.0f);
// uniform vec4 Ks = vec4(0.297254, 0.30729, 0.306678, 1.0f);
// uniform float a = 12.8;

// // Material - Black Plastic
// uniform vec4 Ka = vec4(0.0,  0.0,  0.0,  1.0);
// uniform vec4 Kd = vec4(0.01, 0.01, 0.01, 1.0);
// uniform vec4 Ks = vec4(0.5,  0.5,  0.5,  1.0);
// uniform float a = 32;

void main () {
	//----------------------------------------------
	// Phong Reflection Model
	//----------------------------------------------

	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l = normalize(-frag_Light_Direction);

	// Surface Normal (normalised)
	vec4 n = normalize(frag_Normal);

	// Reflected Vector
	vec4 r = reflect(-l, n);

	// View Vector
	vec4 v = normalize(-frag_Position);

	// ---------- Calculate Terms ----------
	// Ambient Term
	vec4 Ta = Ka * Ia;

	// Diffuse Term
	vec4 Td = Kd * max(dot(l, n), 0.0) * Id;

	// Specular Term
	vec4 Ts = Ks * pow((max(dot(r, v), 0.0)), a) * Is;

	//----------------------------------------------
	// Blinn-Phong Reflection Model
	//----------------------------------------------

	// // ---------- Calculate Vectors ----------
	// // Direction to Light (normalised)
	// vec4 l = normalize(-frag_Light_Direction);

	// // Surface Normal (normalised)
	// vec4 n = normalize(frag_Normal);

	// // Reflected Vector
	// // vec4 r = reflect(-l, n);

	// // View Vector
	// vec4 v = normalize(-frag_Position);

	// // Half Vector
	// vec4 h = normalize(l + v);

	// // ---------- Calculate Terms ----------
	// // Ambient Term
	// vec4 Ta = Ka * Ia;

	// // Diffuse Term
	// vec4 Td = Kd * max(dot(l, n), 0.0) * Id;

	// // Specular Term
	// // vec4 Ts = Ks * pow((max(dot(h, n), 0.0)), a) * Is;
	// vec4 Ts = Ks * pow((max(dot(h, n), 0.0)), 4.0f*a) * Is;

	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	// pixel_Colour = Ta + Td + Ts;
	pixel_Colour = Td + Ts;
}