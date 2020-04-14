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


// Light Source
//in vec4 frag_Light_Direction;  //光源 方向
//uniform vec4 frag_Light_Direction = vec4(-1.0f, 0.0f, 0.0f, 0.0f);  //光源 方向
//uniform vec4 u_Light_position = vec4(0.0f, 0.0f, 0.0f, 0.0f);  //光源 位置
uniform vec4 u_Light_position = vec4(0.0f, 20.0f, 0.0f, 0.0f);  //光源 位置
//uniform mat4 _Light_Direction_angle ;

uniform vec4 light_ambient = vec4(01.0f, 1.0f, 1.0f,1.0f); // 环境光为0 显示材质本来颜色 light color
//uniform vec4 light_diffuse =  vec4(1.0f, 1.0f, 1.0f,1.0f);
//uniform vec4 light_specular = vec4(1.0f, 1.0f, 1.0f,1.0f);

uniform float light_constant = 1.0f;
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform vec4 material_diffuse =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform float material_shininess = 27.89743616;

uniform vec4 cameraPos = vec4 (0.0f,  0.0f,  10.0f,1.0f);

uniform vec4  ambientColor = vec4(0.1f, 0.1f, 0.1f,1.0f);
uniform vec4  objColor = vec4 (1.0f, 1.0f, 1.0f,1.0f);


void main () {
	float dis = length(u_Light_position - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));

	vec4 lightDir = normalize(u_Light_position - frag_Position);

	vec4 reflectVec = reflect(-lightDir, frag_Normal);

	vec4 cameraVec = normalize( cameraPos - frag_Position);

	vec4 Normal =  normalize(frag_Normal);


//	vec4 ambient = ambientColor * texture(material.diffuse, texCoord).rgb;
//	vec4 Target_ambient =  material_ambient *light_ambient; //todo
	vec4 Target_ambient =  material_ambient *ambientColor;
//	vec4 Ta = texture(u_texture_Map,frag_UV.xy)* Ia;

	vec4 Target_diffuse = texture(u_texture_Map, frag_UV.xy) * max(dot(lightDir, Normal), 0) * light_ambient;// todo lightColor

	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material_shininess);

	vec4 Target_specular = material_specular * specularAmount * light_ambient; // todo lightColor

	//漫反射光即为光线跟反射点的法向量点乘
	//	vec3 diffuse = texture(material.diffuse, texCoord).rgb;
//	pixel_Colour = vec4((diffuse + ambient + specular) * objColor, 1.0f);
	pixel_Colour =( Target_ambient * attenuation  + Target_diffuse * attenuation + Target_specular * attenuation)*objColor;


}