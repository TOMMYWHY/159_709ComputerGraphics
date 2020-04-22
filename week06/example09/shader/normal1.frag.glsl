// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_Position;
in vec4 frag_UV;
in vec4 frag_Light_Direction;
in vec3 frag_Normal;
in vec3 frag_Tangent;
in vec3 frag_Bitangent;

// Light Source
uniform vec4 Ia = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Material Coefficients
vec4 Ka = vec4(0.1f, 0.1f, 0.1f, 1.0f);
vec4 Kd = vec4(0.8f, 0.8f, 0.8f, 1.0f);
vec4 Ks = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform float a = 5;

// Texture
uniform sampler2D u_Texture_Map;
uniform sampler2D u_Normal_Map;
uniform sampler2D u_Specular_Map;

// Normal Map Mode
uniform int u_Normal_Map_Mode;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	// Fetch Normal Map
	vec4 normalMap = vec4(normalize(texture(u_Normal_Map, frag_UV.xy).rgb * 2.0f - 1.0f), 0.0f);

	// ---------- Calculate Vectors ----------
	// Normal Vector
	vec4 n = vec4(frag_Normal, 0.0f);

	// If Normal Mapping Enabled
	if(u_Normal_Map_Mode == 1) {
		// Calculate
		n = vec4(frag_Tangent   * normalMap.x +
				 frag_Bitangent * normalMap.y +
				 frag_Normal    * normalMap.z, 0.0f);
	}

//	 pixel_Colour = n; return;
	
	// Direction to Light (normalised)
	vec4 l = normalize(-frag_Light_Direction);

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
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = Ta + Td + Ts;
}