#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 u_camera_Postion; //

uniform vec4 Ia = vec4( 0.1f,0.1f,0.1f,0.0f );//环境光
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);// 光源 颜色
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);//// 镜面反射 光源颜色

uniform vec4 light_postion = vec4 (0.0f, 0.0f, 0.0f,0.0f); // 光源位置
uniform float light_constant = 1.0f; // 光源 衰减系数
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

uniform vec4 u_light_Dir; // 平行光 方向

//uniform sampler2D u_texture_Map;
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform sampler2D material_diffuse ;
uniform vec4 material_specular =vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform float material_shininess = 32.89743616;

void main(){
	vec4 dirToCamera = normalize(u_camera_Postion  - frag_Position);
	vec4 n = normalize(frag_Normal);
	vec4 l   = normalize(light_postion - frag_Position);//lightDirection
	vec4 v    = normalize(dirToCamera - frag_Position);
//	vec4 v = normalize(-frag_Position);

	vec4 r =normalize( reflect( -(l) , n));

	float dis = length(light_postion - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));



	vec4 Ka = texture(material_diffuse, frag_UV.xy);
	vec4 Kd = Ka;
//	vec4 Ks = texture(u_Specular_Map, frag_UV.xy);

	vec4 Target_a = Ka * Ia;
//	vec4 ambColor =texture(material_diffuse,frag_UV.xy) * ambinetColor;

	// Diffuse Term
	vec4 Target_d = Kd * max(dot(l, n), 0.0) * Id;
//	float diffIntensity = max(dot( normalize(lightDir )  ,uNormal), 0);
//	vec4 diffuseColor = diffIntensity * light.color * (texture(material_diffuse , frag_UV.xy)) ;
//	diffuseColor = pow(diffuseColor,vec4(gamma));


	// Specular Term
	vec4 Target_s = material_specular * pow((max(dot(r, v), 0.0)), material_shininess) * Is;
//	vec4 Ts = Ks * pow((max(dot(n, v), 0.0)), a) * Is;
//	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0), material_shininess);
//	vec4 specularColor = specIntensity * light.color * (material_specular) ;

	pixel_Colour = (Target_a + Target_d + Target_s)*attenuation;


//	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);
}


/*
vec4 CalcLightPoint(LightPoint light,vec4 uNormal, vec4 dirToCamera){
	vec4 lightDir   = normalize(light.pos - frag_Position);
	vec4 viewDir    = normalize(dirToCamera - frag_Position);
	vec4 halfwayDirhalfwayDir = normalize(lightDir + viewDir);

	//attenuation
	float dis = length(light.pos - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));
	// ambient
	vec4 ambColor =texture(material_diffuse,frag_UV.xy) * ambinetColor;
	// difuse
	float diffIntensity = max(dot( normalize(lightDir )  ,uNormal), 0);
//	vec4 diffuseColor = diffIntensity * light.color * pow(texture(material_diffuse , frag_UV.xy),vc4(gamma)) ;
	vec4 diffuseColor = diffIntensity * light.color * (texture(material_diffuse , frag_UV.xy)) ;
	diffuseColor = pow(diffuseColor,vec4(gamma));
	//specular
	vec4 r =normalize( reflect( -(normalize(lightDir) ), uNormal)); // todo 去掉 normalize
	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0), material_shininess);
	vec4 specularColor = specIntensity * light.color * (material_specular) ;
	vec4 result =(ambColor+ diffuseColor + specularColor)  * attenuation;
	return result;
}

*/

/*

void main()
{
	vec4 uNormal = normalize(frag_Normal);
	vec4 dirToCamera = normalize(u_camera_Postion  - frag_Position);
	finalResult += CalcLightPoint(lightP,uNormal, dirToCamera);


	pixel_Colour = finalResult;
	pixel_Colour = pow(pixel_Colour,vec4(1.0/gamma));
//	pixel_Colour = (pixel_Colour);
	//	pixel_Colour = objColor * ambinetColor;
//	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);
}
*/