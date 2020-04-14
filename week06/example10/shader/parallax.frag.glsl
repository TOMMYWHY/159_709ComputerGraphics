// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_Position;
in vec4 frag_UV;
in vec4 frag_Light_Direction;
in mat4 i_Tangent;

// Light Source
uniform vec4 Ia = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Material - Brick
uniform float a = 5;

// Texture
uniform sampler2D u_Texture_Map;  // Diffuse Texture
uniform sampler2D u_Surface_Map;  // Surface (Normal, Height)
uniform sampler2D u_Specular_Map; // Specular Texture

// Parallax Mode
uniform int u_Parallax_Mode = 0;

// Output from Fragment Shader
out vec4 pixel_Colour;

// --------------------------------------------------------------------------------
// Linear search for an intersection
float linear_search_intersection(vec2 uv_in, vec2 uv_out, vec3 v, int LIN_ITERATIONS) {
	// Intersection
	float h_intersection = 0.0f;

	// Linear Search Step
	float step = 1.0f / LIN_ITERATIONS;

	// Linear Search
	for(int i = 0; i < LIN_ITERATIONS; i++) {
		// New height
		float h_i = 1.0f - (i * step);

		// UV Coordinate
		vec2 uv = (uv_in * h_i) + uv_out * (1.0f-h_i);

		// Get Height
		float h = (texture(u_Surface_Map, uv).a);

		// Height of ray is less than height of surface
		if((h_intersection == 0.0f) && (h_i <= h)) {
			// Intersection found
			h_intersection = h_i;
			return h_i;
		}
	}

	// Return intersection
	return h_intersection;
}

// Linear search for UV coordinate of intersection
vec2 linear_search(vec2 uv_in, vec2 uv_out, vec3 v, int LIN_ITERATIONS) {
	// Find intersection
	float h_intersection = linear_search_intersection(uv_in, uv_out, v, LIN_ITERATIONS);

	// Calculate first point after/at intersection
	vec2 uv = uv_in * h_intersection + uv_out * (1.0f-h_intersection);

	// Return texture coordinate
	return uv;
}

// --------------------------------------------------------------------------------
// Binary search for an intersection
float binary_search_intersection(vec2 uv_in, vec2 uv_out, vec3 v, float h_min, float h_max, int BIN_ITERATIONS) {
	// Binary Search
	for(int i = 0; i < BIN_ITERATIONS; i++) {
		// Middle Point
		float mid = (h_min + h_max) * 0.5f;

		// Calculate UV Coordinate
		vec2 uv = uv_in * mid + uv_out * (1.0f-mid);

		// Get Height
		float h = (texture(u_Surface_Map, uv).a);

		// Binary Search Window
		if(mid <= h) {
			h_min = mid;
		} else {
			h_max = mid;
		}
	}

	// Return best guess at intersection
	return (h_min + h_max) * 0.5f;
}

// Binary search for UV coordinate of intersection
vec2 binary_search(vec2 uv_in, vec2 uv_out, vec3 v, float h_min, float h_max, int BIN_ITERATIONS) {
	// ------- Parallax Mapping Binary Search  -------
	// Find Intersection
	float mid = binary_search_intersection(uv_in, uv_out, v, h_min, h_max, BIN_ITERATIONS);

	// Return UV Coordinate
	return uv_in * mid + uv_out * (1.0f-mid);
}

// --------------------------------------------------------------------------------
// Secant search for an intersection
float secant_search_intersection(vec2 uv_in, vec2 uv_out, vec3 v, float h_a, float h_b, int SEC_ITERATIONS) {
	// Calculate UV coordinates of a and b
	vec2 uv_a = uv_in * h_a + uv_out * (1.0f-h_a);
	vec2 uv_b = uv_in * h_b + uv_out * (1.0f-h_b);

	// Height differences between ray and surface
	float d_a = texture(u_Surface_Map, uv_a).a - h_a;
	float d_b = texture(u_Surface_Map, uv_b).a - h_b;

	// Secant Search

	for(int i = 0; i < SEC_ITERATIONS; i++) {
		// Calculate mid-point height
		float mid = h_a + (h_b - h_a) / (d_a - d_b) * d_a;

		// Calculate UV Coordinate
		vec2 uv = uv_in * mid + uv_out * (1.0f-mid);

		// Calculate height difference between ray and surface
		float d = (texture(u_Surface_Map, uv).a) - mid;

		// Update search range
		if(d < 0) {
			d_b = d;
			h_b = mid;
		} else {
			d_a = d;
			h_a = mid;
		}
	}

	// Return best guess at intersection
	return h_a + (h_b - h_a) / (d_a - d_b) * d_a;
}

// Secant search for UV coordinate of intersection
vec2 secant_search(vec2 uv_in, vec2 uv_out, vec3 v, float h_a, float h_b, int SEC_ITERATIONS) {
	// ------- Parallax Mapping Binary Search  -------
	// Find Intersection
	float intersection = secant_search_intersection(uv_in, uv_out, v, h_a, h_b, SEC_ITERATIONS);

	// Return UV Coordinate
	return uv_in * intersection + uv_out * (1.0f - intersection);
}
// --------------------------------------------------------------------------------

void main () {
	//----------------------------------------------
	// Relief Mapping
	//----------------------------------------------

	// Normalised View Vector (Tangent Space)
	vec4 v = vec4(normalize(-frag_Position.xyz), 0.0f);

	// Bias parameters
	// float scale =  0.01;
	float scale =  0.05;
	// float scale =  0.1;
	// float scale =  0.2;

	// Bias Parameter
	// float bias  =  0.0;
	// float bias  = -0.0075;
	float bias  = -0.02;
	// float bias  = -0.0375;
	// float bias  = -0.075;
	// float bias  = -0.15;

	// UV Coordinate
	vec2 uv = frag_UV.xy;

	// Select Parallax Mapping Method
	if(u_Parallax_Mode == 0) {
		// ------- No Parallax Mapping -------
		uv = frag_UV.xy;
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 1) {
		// ------- Parallax Mapping -------
		// Fetch Height
		float h = texture(u_Surface_Map, frag_UV.xy).a * scale + bias;

		// Calculate UV Coordinate
		uv = frag_UV.xy + (h * v.xy) / v.z;
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 2) {
		// ------- Parallax Mapping (Offset Limiting) -------
		// Fetch Height
		float h = texture(u_Surface_Map, frag_UV.xy).a * scale + bias;

		// Calculate UV Coordinate
		uv = frag_UV.xy + (h * v.xy);
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 3) {
		// ------- Parallax Mapping (Account for Slope) -------
		// Fetch Surface
		vec4 surface = texture(u_Surface_Map, uv);

		// Get Normal
		vec4 norm = vec4(normalize(surface.xyz * 2.0f - 1.0f), 0.0f);

		// Get Height
		float h = surface.a * scale + bias;

		// Calculate UV Coordinate
		uv = frag_UV.xy + (norm.z * h * v.xy);
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 4) {
		// ------- Parallax Mapping Iterative Solution -------
		// Number of Search Iterations
		int PAR_ITERATIONS = 5;
		
		// Initial Guess
		vec3 uvh = vec3(uv, 0.0f);

		// Iteratively Search
		for(int i = 0; i < PAR_ITERATIONS; i++) {
			// Fetch Surface
			vec4 surface = texture(u_Surface_Map, uvh.xy);

			// Get Normal
			vec4 norm = vec4(normalize(surface.xyz * 2.0f - 1.0f), 0.0f);

			// Get Height
			float h = surface.a * scale + bias;

			// Calculate next iteration
			uvh = uvh + (h - uvh.z) * norm.z * v.xyz;
		}

		// Get UV coordinate
		uv = uvh.xy;
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 5) {
		// ------- Parallax Mapping Binary Search  -------
		// Number of Search Iterations
		int BIN_ITERATIONS = 10;

		// Extreme points where ray could enter/exit surface
		vec2 uv_out = uv + (0.0f * scale + bias) * v.xy;
		vec2 uv_in  = uv + (1.0f * scale + bias) * v.xy;

		// Binary Search for UV Coordinate
		uv = binary_search(uv_in, uv_out, v.xyz, 0.0f, 1.0f, BIN_ITERATIONS);
		// ----------------------------------------------------
	} else if(u_Parallax_Mode == 6) {
		// ------- Parallax Mapping Secant Method  -------
		// Number of Search Iterations
		int SEC_ITERATIONS = 10;

		// Extreme points where ray could enter/exit surface
		vec2 uv_in  = uv + (1.0f * scale + bias) * v.xy;
		vec2 uv_out = uv + (0.0f * scale + bias) * v.xy;

		// Secant Search for UV Coordinate
		uv = secant_search(uv_in, uv_out, v.xyz, 0.0f, 1.0f, SEC_ITERATIONS);
	} else if(u_Parallax_Mode == 7) {
		// ------- Parallax Mapping Linear Search  -------
		// Number of Search Iterations
		// int LIN_ITERATIONS = 5;
		int LIN_ITERATIONS = 25;

		// Extreme points where ray could enter/exit surface
		vec2 uv_in  = uv + (1.0f * scale + bias) * v.xy;
		vec2 uv_out = uv + (0.0f * scale + bias) * v.xy;

		// Find Texture Coordinate
		uv = linear_search(uv_in, uv_out, v.xyz, LIN_ITERATIONS);
	} else if(u_Parallax_Mode == 8) {
		// ------- Parallax Mapping Linear Search - Binary Search -------
		// Number of Search Iterations
		// int LIN_ITERATIONS = 5;
		// int BIN_ITERATIONS = 3;
		int LIN_ITERATIONS = 25;
		int BIN_ITERATIONS = 5;

		// Extreme points where ray could enter/exit surface
		vec2 uv_in  = uv + (1.0f * scale + bias) * v.xy;
		vec2 uv_out = uv + (0.0f * scale + bias) * v.xy;

		// Linear Search for points either side of intersection
		float a = linear_search_intersection(uv_in, uv_out, v.xyz, LIN_ITERATIONS);
		float b = a + 1.0 / LIN_ITERATIONS;

		// Binary Search for intersection
		float c = binary_search_intersection(uv_in, uv_out, v.xyz, a, b, BIN_ITERATIONS);

		// Calculate UV Coordinate
		uv = (uv_in * c) + uv_out * (1.0f - c);
	} else if(u_Parallax_Mode == 9) {
		// ------- Parallax Mapping Linear Search - Secant Search -------
		// Number of Linear Search Iterations
		// int LIN_ITERATIONS = 5;
		// int SEC_ITERATIONS = 3;
		int LIN_ITERATIONS = 25;
		int SEC_ITERATIONS = 5;

		// Extreme points where ray could enter/exit surface
		vec2 uv_in  = uv + (1.0f * scale + bias) * v.xy;
		vec2 uv_out = uv + (0.0f * scale + bias) * v.xy;

		// Linear Search for points either side of intersection
		float a = linear_search_intersection(uv_in, uv_out, v.xyz, LIN_ITERATIONS);
		float b = a + 1.0 / LIN_ITERATIONS;

		// Secant Search for intersection
		float c = secant_search_intersection(uv_in, uv_out, v.xyz, a, b, SEC_ITERATIONS);

		// Calculate UV Coordinate
		uv = (uv_in * c) + uv_out * (1.0f - c);
	}

	//----------------------------------------------
	// Phong Reflection Model
	//----------------------------------------------
	// Fetch Ambient Coefficients
	vec4 Ka = texture(u_Texture_Map, uv);

	// Fetch Diffuse Coefficients
	vec4 Kd = Ka;

	// Fetch Specular Coefficients
	vec4 Ks = texture(u_Specular_Map, uv);

	// ---------- Calculate Vectors ----------
	// Direction to Light (Tangent Space)
	vec4 l = normalize(-frag_Light_Direction);

	// Normal (Tangent Space)
	vec4 n = vec4(normalize(texture(u_Surface_Map, uv).rgb * 2.0f - 1.0f), 0.0f);

	// Reflected Vector (Tangent Space)
	vec4 r = reflect(-l, n);

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