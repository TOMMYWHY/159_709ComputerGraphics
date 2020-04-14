// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_UV;

in vec4 frag_Position;
in vec4 frag_Normal;
// Texture
uniform sampler2D u_texture_Map;

// Output from Fragment Shader
out vec4 pixel_Colour;

struct Material
{
	vec4 ambient;
	sampler2D diffuse;
//	sampler2D specular;
	vec4 specular;
	float shininess;
};
uniform Material material;

struct LightPoint
{
	float constant;
	float linear;
	float quadratic;
};
uniform LightPoint lightPoint;

// Light Source
//in vec4 frag_Light_Direction;  //光源 方向
//uniform vec4 frag_Light_Direction = vec4(-1.0f, 0.0f, 0.0f, 0.0f);  //光源 方向
uniform vec4 u_Light_position = vec4(1.0f, 0.0f, 0.0f, 0.0f);  //光源 位置
//uniform mat4 _Light_Direction_angle ;

uniform vec4 Ia = vec4(0.5f, 0.5f, 0.5f, 1.0f); // 环境光为0 显示材质本来颜色 light color
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

/*
// Material - Brass
uniform vec4 Ka = vec4(0.329412, 0.223529, 0.027451, 1.0);
uniform vec4 Kd = vec4(0.780392, 0.568627, 0.113725, 1.0);
uniform vec4 Ks = vec4(0.992157, 0.941176, 0.807843, 1.0);
uniform float a = 27.89743616;
*/

void main () {
/*	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------

	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l =normalize(-u_Light_position+frag_Position);
//	vec4 l = normalize(-frag_Light_Direction);

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
//	vec4 Ta = texture(u_texture_Map,frag_UV.xy)* Ia;

	// Diffuse Term
//		vec4 Td = Kd * max(dot(l, n), 0.0) * Id;
	//	vec4 Td = (material.diffuse) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)
//	vec4 Td = texture(material.diffuse,frag_UV.xy) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)
	vec4 Td = texture(u_texture_Map,frag_UV.xy) * max(dot(l, n), 0.0) * Id; // 漫反射 与 入射光，物体法向量 ，物体漫反射系数(颜色Kd)

	// Specular Term
//		vec4 Ts = Ks * pow((max(dot(r, v), 0.0)), a) * Is;
	vec4 Ts = material.specular * pow((max(dot(r, v), 0.0)), material.shininess) * Is;
//	vec4 Ts = texture(material.specular,frag_UV.xy) * pow((max(dot(r, v), 0.0)), material.shininess) * Is;


	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = Ta + Td + Ts;
	//	pixel_Colour = Td + Ts;

	//	pixel_Colour = texture(u_texture_Map, frag_UV.xy);*/




	float dis = length(u_Light_position - frag_Position);
	float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dis+lightPoint.quadratic * (dis * dis));

	vec4 l = normalize(u_Light_position - frag_Position);

	vec4 r = reflect(-l, frag_Normal);
//	vec4 r = reflect(-l, frag_Normal);

//	vec4 cameraVec = normalize(cameraPos - frag_Position);
	vec4 n = normalize(frag_Normal);

	vec4 v = normalize( - frag_Position);

//	vec4 ambient = ambientColor * texture(material.diffuse, texCoord).rgb;
	vec4 Ta =  (material.ambient) *Ia;
//	vec4 Ta = texture(u_texture_Map,frag_UV.xy)* Ia;

	vec4 Td = texture(u_texture_Map, frag_UV.xy) * max(dot(l, n), 0) * Id;

	float specularAmount = pow(max(dot(r, v), 0), material.shininess);
	vec4 Ts = (material.specular) * specularAmount * Is;

	//漫反射光即为光线跟反射点的法向量点乘
	//	vec3 diffuse = texture(material.diffuse, texCoord).rgb;
//	pixel_Colour = vec4((diffuse + ambient + specular) * objColor, 1.0f);
	pixel_Colour = Ta  + Td * attenuation + Ts * attenuation;


}