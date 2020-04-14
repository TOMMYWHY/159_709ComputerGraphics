// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_UV;

in vec4 frag_Position;
in vec4 frag_Normal;
in vec4 frag_Light_Direction;

// Output from Fragment Shader
out vec4 pixel_Colour;


struct Material
{
	vec4 ambient;
	sampler2D diffuse;
	vec4 specular;
	float shininess;
};
uniform Material material;

// Light Source
uniform vec4 Ia = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

 // Material - Brass
uniform vec4 Ka = vec4(0.329412, 0.223529, 0.027451, 1.0);
uniform vec4 Kd = vec4(0.780392, 0.568627, 0.113725, 1.0);
uniform vec4 Ks = vec4(0.992157, 0.941176, 0.807843, 1.0);
uniform float a = 27.89743616;

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
//	vec4 Ta = Ka * Ia;
	vec4 Ta = material.ambient * Ia;


	// Diffuse Term
//	vec4 Td = Kd * max(dot(l, n), 0.0) * Id;
//	vec4 Td = (material.diffuse) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)
	vec4 Td = texture(material.diffuse,frag_UV.xy) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)


	// Specular Term
//	vec4 Ts = Ks * pow((max(dot(r, v), 0.0)), a) * Is;
	vec4 Ts = material.specular * pow((max(dot(r, v), 0.0)), material.shininess) * Is;


	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	 pixel_Colour = Ta + Td + Ts;
//	pixel_Colour = Td + Ts;
}