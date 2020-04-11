// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_UV;

in vec4 frag_Position;
in vec4 frag_Normal;
in vec4 frag_Light_Direction;

// Texture
uniform sampler2D u_texture_Map;


// Light Source
//uniform vec4 Ia = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform vec4 Ia = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

struct Material {
	vec4 ambient;
	sampler2D diffuse;
	vec4 specular;
	float shininess;
};
uniform Material material;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {


	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l = normalize(-frag_Light_Direction);

	// Surface Normal (normalised)
	vec4 n = normalize(frag_Normal);

	// Reflected Vector
	vec4 r = reflect(-l, n);

	// View Vector
	vec4 v = normalize(-frag_Position); // 人眼位置(camera) cameraPos - frag_postion

	// ---------- Calculate Terms ----------
	// Ambient Term
	vec4 Ta = material.ambient * Ia;

	// Diffuse Term
//	vec4 Td = texture(material.diffuse,frag_UV.xy) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)
	vec4 Td = texture(u_texture_Map,frag_UV.xy) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)

	// Specular Term
	vec4 Ts = material.specular * pow((max(dot(r, v), 0.0)), material.shininess) * Is;

	pixel_Colour = Ta + Td + Ts;

	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
//	pixel_Colour = texture(u_texture_Map, frag_UV.xy);
}