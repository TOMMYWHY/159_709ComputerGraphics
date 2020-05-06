// OpenGL 4.0
#version 400

layout (triangles, equal_spacing, ccw) in;
// layout (triangles, fractional_odd_spacing, ccw) in;
// layout (triangles, fractional_even_spacing, ccw) in;
// layout (quads, equal_spacing, ccw) in;
// layout (quads, fractional_odd_spacing, ccw) in;
// layout (quads, fractional_even_spacing, ccw) in;

// Input from Evaluation Shader
in vec4 eval_Position[];
in vec4 eval_Colour[];

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Colour;

// Texture
uniform sampler2D u_texture_Map;

uniform float u_time;

void main() {
	//----------------------------------------------
	// Triangles - Stationary
	//----------------------------------------------
	
	// Position
	vec3 pos0 = gl_TessCoord.x * eval_Position[0].xyz;
	vec3 pos1 = gl_TessCoord.y * eval_Position[1].xyz;
	vec3 pos2 = gl_TessCoord.z * eval_Position[2].xyz;
	vec3 position = pos0 + pos1 + pos2;

	// Colour
	vec3 colour0 = gl_TessCoord.x * eval_Colour[0].xyz;
	vec3 colour1 = gl_TessCoord.y * eval_Colour[1].xyz;
	vec3 colour2 = gl_TessCoord.z * eval_Colour[2].xyz;
	vec3 colour = colour0 + colour1 + colour2;

	//----------------------------------------------
	// Quad - Stationary
	//----------------------------------------------

	// // Position
	// vec3 pos_a = mix(eval_Position[0].xyz, eval_Position[1].xyz, gl_TessCoord.x);
	// vec3 pos_b = mix(eval_Position[3].xyz, eval_Position[2].xyz, gl_TessCoord.x);
	// vec3 position = mix(pos_a, pos_b, gl_TessCoord.y);

	// // Colour
	// vec3 colour_a = mix(eval_Colour[0].xyz, eval_Colour[1].xyz, gl_TessCoord.x);
	// vec3 colour_b = mix(eval_Colour[3].xyz, eval_Colour[2].xyz, gl_TessCoord.x);
	// vec3 colour = mix(colour_a, colour_b, gl_TessCoord.y);

	//----------------------------------------------
	// Quad - Sine Wave
	//----------------------------------------------

	// // Position
	// vec3 pos_a = mix(eval_Position[0].xyz, eval_Position[1].xyz, gl_TessCoord.x);
	// vec3 pos_b = mix(eval_Position[3].xyz, eval_Position[2].xyz, gl_TessCoord.x);
	// vec3 position = mix(pos_a, pos_b, gl_TessCoord.y);

	// // Add Sine wave
	// position.z += 0.1f*sin(position.x * 6.28f + u_time*2.0f);

	// // Colour
	// vec3 colour_a = mix(eval_Colour[0].xyz, eval_Colour[1].xyz, gl_TessCoord.x);
	// vec3 colour_b = mix(eval_Colour[3].xyz, eval_Colour[2].xyz, gl_TessCoord.x);
	// vec3 colour = mix(colour_a, colour_b, gl_TessCoord.y);

	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Position
	frag_Position = u_View * u_Model * vec4(position, 1.0f);

	// Colour
	frag_Colour = vec4(colour, 0.0f);

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
}