#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 Ia = vec4( 0.2f,0.2f,0.2f,0.0f );//环境光
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);// 光源 颜色
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);//// 镜面反射 光源颜色

uniform vec4 light_postion = vec4 (0.0f, 0.0f, 5.0f,0.0f); // 光源位置
uniform float light_constant = 1.0f; // 光源 衰减系数
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

//uniform vec4 u_light_Dir; // 平行光 方向

uniform sampler2D material_diffuse ;
uniform sampler2D material_specular ;
uniform sampler2D material_Normal;

uniform float material_shininess = 32.89743616;
uniform float gamma = 2.2;



void main()
{
	vec4 Ka = texture(material_diffuse, frag_UV.xy);
	//	vec4 Ka = texture(material_specular, frag_UV.xy);
	//	vec4 Ka = vec4(1.0f, 1.0f, 1.0f, 0.1f);
	vec4 Kd = Ka;
	//	vec4 Ks = vec4(1.0f, 1.0f, 1.0f, 0.1f);
	vec4 Ks = texture(material_specular, frag_UV.xy); // specular effect not working

	vec4 uNormal = normalize(frag_Normal);
	//		vec4 uNormal= vec4(normalize(texture(material_Normal, frag_UV.xy).rgb * 2.0f - 1.0f), 0.0f);

	vec4 lightDir   = normalize(light_postion - frag_Position);
	vec4 viewDir    = normalize( - frag_Position);
	vec4 halfwayDir = normalize(lightDir + viewDir);
	//attenuation
	float dis = length(light_postion - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));

	// ambient
	vec4 Target_a =Ka * Ia;

	// difuse
	float diffIntensity = max(dot( normalize(lightDir )  ,uNormal), 0);
	vec4 Target_d = diffIntensity * Kd * Id  ;
	Target_d = pow(Target_d,vec4(gamma));

	//specular
	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0), material_shininess);
	vec4 Target_s = specIntensity * Ks *Is ;

	pixel_Colour =(Target_a+ Target_d + Target_s)  * attenuation;
	//	pixel_Colour =Target_s;
	//	pixel_Colour =Target_a;

	pixel_Colour = pow(pixel_Colour,vec4(1.0/gamma));
}