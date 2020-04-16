#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 u_camera_Postion; //

//uniform sampler2D ourTexture;
//uniform sampler2D ourTextureFace;
uniform vec4 objColor; //obj 表面颜色 // 可为0
uniform vec4 ambinetColor; //环境光 // 应该为0
uniform vec4 u_Light_Postion; // 光源位置
uniform vec4 lightColor; // 光源 颜色
uniform float light_constant = 1.0f; // 光源 衰减系数
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

//uniform vec4 u_light_Dir; // 平行光 方向

uniform sampler2D u_texture_Map;
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
//uniform vec4 material_diffuse =  vec4(1.0f, 1.0f, 1.0f,1.0f);
//uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform sampler2D material_specular ;
// uniform vec4 material_specular =vec4(1.0f, 1.0f, 1.0f,1.0f) ;
uniform float material_shininess = 32.89743616;


//uniform vec4 ourColor;
void main()
{
	float dis = length(u_Light_Postion - frag_Position);

	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));

	vec4 light_Dir = normalize(u_Light_Postion - frag_Position);


	//	vec4 light_Dir = u_light_Dir; // for 平行光 方向
	vec4 n = normalize(frag_Normal); //一定 一定 要改成单位向量
	vec4 r = reflect(-light_Dir, n);
	vec4 v = normalize(u_camera_Postion  - frag_Position);


	vec4 Target_ambient =texture(u_texture_Map,frag_UV.xy) * ambinetColor;

	float specularAmount = pow(max(dot(r, v), 0), material_shininess);
	vec4 Target_specular = texture(material_specular,frag_UV.xy) * specularAmount * lightColor;
//	vec4 Target_specular = (material_specular) * specularAmount * lightColor;

	vec4 Target_diffuse = texture(u_texture_Map,frag_UV.xy) * max(dot(light_Dir,n), 0)  * lightColor ;
//	vec4 Target_diffuse =  max(dot(light_Dir,frag_Normal), 0)  * lightColor ;




//	pixel_Colour = objColor * ambinetColor;
	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);
}