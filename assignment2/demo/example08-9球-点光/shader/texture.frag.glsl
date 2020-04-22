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



// Light Source
//in vec4 frag_Light_Direction;  //光源 方向
//in vec4 frag_Light_position;
//uniform vec4 frag_Light_Direction = vec4(-1.0f, 0.0f, 0.0f, 0.0f);  //光源 方向
uniform vec4 frag_Light_position = vec4(0.0f, 0.0f, 0.0f, 1.0f);  //光源
uniform vec4 u_Light_color = vec4(1.0, 1.0f, 1.0f, 1.0f);  //光颜色， 光强
//uniform mat4 _Light_Direction_angle ;
uniform float light_constant = 1.0f;
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

//uniform vec4 Ia = vec4(0.5f, 0.5f, 0.5f, 1.0f); // 环境光为0 显示材质本来颜色 light color
//uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform vec4 material_ambient =  vec4(.1f, .1f, .1f, 1.0f);
uniform vec4 material_diffuse =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform float material_shininess = 27.89743616;

uniform vec4 objColor =  vec4( 1.0f, 1.0f, 1.0f,1.0f);
uniform vec4 ambientColor =  vec4(  0.1f, 0.1f, 0.1f,1.0f);

void main () {

	float dis = length(frag_Light_position - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));

	vec4 l = normalize(frag_Light_position - frag_Position);//light direction
	vec4 r = reflect(-l, frag_Normal);
	vec4 n = normalize(frag_Normal);
	vec4 v = normalize(  - frag_Position);
	vec4 Target_ambient =  ambientColor * texture(u_texture_Map, frag_UV.xy); // todo ambientColor

	vec4 Target_diffuse = texture(u_texture_Map, frag_UV.xy) * max(dot(l, n), 0) * u_Light_color;

	float specularAmount = pow(max(dot(r, v), 0), material_shininess);
	vec4 Target_specular = (material_specular) * specularAmount * u_Light_color;

	//漫反射光即为光线跟反射点的法向量点乘
	//	pixel_Colour = Ta  + Td * attenuation + Ts * attenuation;
	//	pixel_Colour = Ta  + Td  + Ts ;

	pixel_Colour = ((Target_ambient + (Target_diffuse + Target_specular) * attenuation) * objColor);



}