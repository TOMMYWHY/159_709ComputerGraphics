#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 u_camera_Postion; //

//uniform sampler2D ourTexture;
//uniform sampler2D ourTextureFace;
uniform vec4 ambinetColor =  vec4( 0.3f,0.3f,0.3f,0.0f ); //环境光
uniform vec4 u_Light_Postion; // 光源位置
uniform vec4 u_Light_Color; // 光源 颜色
uniform float light_constant = 1.0f; // 光源 衰减系数
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

uniform vec4 u_light_Dir; // 平行光 方向

//uniform sampler2D u_texture_Map;
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform sampler2D material_diffuse ;
//uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform vec4 material_specular =vec4(1.0f, 1.0f, 1.0f, 0.1f);
// uniform vec4 material_specular =vec4(1.0f, 1.0f, 1.0f,1.0f) ;
uniform float material_shininess = 32.89743616;
struct LightDirectional{
	vec4 pos;
	vec4 color;
	vec4 dirToLight;
};

struct LightPoint{
	vec4 pos;
	vec4 color;
};

struct LightSpot{
	vec4 pos;
	vec4 color;
	vec4 dirToLight;
	float cosPhyInner;
	float cosPhyOuter;
};
//uniform LightDirectional lightD;
uniform LightPoint lightP;
//uniform LightSpot lightS;




vec4 CalcLightPoint(LightPoint light,vec4 uNormal, vec4 dirToCamera){
	//attenuation
	float dis = length(light.pos - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));
	// ambient
	vec4 ambColor =texture(material_diffuse,frag_UV.xy) * ambinetColor;
	// difuse
	float diffIntensity = max(dot( normalize(light.pos - frag_Position )  ,uNormal), 0);
	vec4 diffuseColor = diffIntensity * light.color * texture(material_diffuse , frag_UV.xy) ;
	//specular
	vec4 r =normalize( reflect( -(normalize(light.pos - frag_Position) ), uNormal)); // todo 去掉 normalize
	float specIntensity = pow(max(dot(r, dirToCamera), 0), material_shininess);
//	vec4 specularColor = specIntensity * light.color * texture(material_specular , frag_UV.xy) * attenuation;
	vec4 specularColor = specIntensity * light.color * (material_specular) ;
	vec4 result =(ambColor+ diffuseColor + specularColor)  * attenuation;
	return result;
}


void main()
{
	vec4 finalResult = vec4 (0,0,0,0);
	vec4 uNormal = normalize(frag_Normal);
	vec4 dirToCamera = normalize(u_camera_Postion  - frag_Position);
	finalResult += CalcLightPoint(lightP,uNormal, dirToCamera);






	pixel_Colour = finalResult;

	//	pixel_Colour = objColor * ambinetColor;
//	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);
}