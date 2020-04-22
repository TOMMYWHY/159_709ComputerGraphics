// OpenGL 3.3
#version 330

// Input from Vertex Shader
in vec4 frag_UV;
in vec4 frag_Position;
in vec4 frag_Normal;


// Output from Fragment Shader
out vec4 pixel_Colour;

// Light Source
uniform vec4 u_camera_Postion; //
uniform vec4 objColor = vec4 (1.0f,1.0f,1.0f,1.0f); //obj 表面颜色 // 可为0
uniform vec4 ambinetColor = vec4(0.1f,0.1f,0.1f,0.0f ); //环境光 // 应该为0
uniform vec4 u_Light_Postion = vec4(0.0f, 0.0f, 0.0f,0.0f); // 光源位置
uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f,1.0f); // 光源 颜色
uniform float light_constant = 1.0f;
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;



// obj
uniform sampler2D u_texture_Map;
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform float material_shininess = 27.89743616;



void main () {

	float dis = length(u_Light_Postion - frag_Position);

	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));
	vec4 light_Dir = normalize(u_Light_Postion - frag_Position);
	vec4 n = normalize(frag_Normal); //一定 一定 要改成单位向量
	vec4 r = reflect(-light_Dir, n);
	vec4 v = normalize(u_camera_Postion  - frag_Position);


	vec4 Target_ambient=texture(u_texture_Map,frag_UV.xy) * ambinetColor;

	float specularAmount = pow(max(dot(r, v), 0), material_shininess);
	vec4 Target_specular = (material_specular) * specularAmount * lightColor;


	vec4 Target_diffuse = texture(u_texture_Map, frag_UV.xy) * max(dot(light_Dir, n), 0) * lightColor;


	//漫反射光即为光线跟反射点的法向量点乘
	//	pixel_Colour = Ta  + Td * attenuation + Ts * attenuation;
	//	pixel_Colour = Ta  + Td  + Ts ;

	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);



}