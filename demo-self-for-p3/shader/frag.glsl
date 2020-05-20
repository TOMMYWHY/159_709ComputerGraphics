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
uniform vec4 u_Light_Color; // 光源 颜色
uniform float light_constant = 1.0f; // 光源 衰减系数
uniform float light_linear = 0.09f;
uniform float light_quadratic = 0.032f;

uniform vec4 u_light_Dir; // 平行光 方向

//uniform sampler2D u_texture_Map;
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform sampler2D material_diffuse ;
//uniform vec4 material_specular =  vec4(1.0f, 1.0f, 1.0f,1.0f);
uniform sampler2D material_specular ;
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
//	vec4 dirToLight;
//	float	constant;
//	float	linear ;
//	float	quadratic;
};

struct LightSpot{
	vec4 pos;
	vec4 color;
	vec4 dirToLight;
	float cosPhyInner;
	float cosPhyOuter;
};
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;



vec4 CalcLightDirectional(LightDirectional light,vec4 uNormal, vec4 dirToCamera){
	// difuse
	float diffIntensity = max(dot(light.dirToLight,uNormal), 0);
	vec4 diffuseColor = diffIntensity * light.color * texture(material_diffuse , frag_UV.xy);
	//specular
	vec4 r =normalize( reflect(-light.dirToLight, uNormal)); // todo 去掉 normalize
	float specIntensity = pow(max(dot(r, dirToCamera), 0), material_shininess);
	vec4 specularColor = specIntensity * light.color * texture(material_specular , frag_UV.xy);;

	vec4 result = diffuseColor + specularColor;
	return result;
}
vec4 CalcLightPoint(LightPoint light,vec4 uNormal, vec4 dirToCamera){
	//attenuation
	float dis = length(light.pos - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));
	// difuse
	float diffIntensity = max(dot( normalize(light.pos - frag_Position )  ,uNormal), 0);
	vec4 diffuseColor = diffIntensity * light.color * texture(material_diffuse , frag_UV.xy);
	//specular
	vec4 r =normalize( reflect( -(normalize(light.pos - frag_Position) ), uNormal)); // todo 去掉 normalize
	float specIntensity = pow(max(dot(r, dirToCamera), 0), material_shininess);
	vec4 specularColor = specIntensity * light.color * texture(material_specular , frag_UV.xy) * attenuation;
	vec4 result =( diffuseColor + specularColor)  * attenuation;
	return result;
}

vec4 CalcLightSpot(LightSpot light,vec4 uNormal, vec4 dirToCamera){
	//attenuation
	float dis = length(light.pos - frag_Position);
	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));
	float spotRatio;
	float cosTheta = dot( normalize(frag_Position - light.pos) , -light.dirToLight);
	if(cosTheta > light.cosPhyInner){
		//inside
		spotRatio = 1.0f;
	}else if(cosTheta > light.cosPhyOuter){
		// middle
		spotRatio = 1.0f -( cosTheta - light.cosPhyInner)/( light.cosPhyOuter -light.cosPhyInner );
	}
	else{
		//outside
		spotRatio = 0.0f;
	}
	// difuse
	float diffIntensity = max(dot( normalize(light.pos - frag_Position )  ,uNormal), 0);
	vec4 diffuseColor = diffIntensity * light.color * texture(material_diffuse , frag_UV.xy);
	//specular
	vec4 r =normalize( reflect( -(normalize(light.pos - frag_Position) ), uNormal)); // todo 去掉 normalize
	float specIntensity = pow(max(dot(r, dirToCamera), 0), material_shininess);
	vec4 specularColor = specIntensity * light.color * texture(material_specular , frag_UV.xy) ;
	vec4 result =( diffuseColor + specularColor)  * attenuation * spotRatio;
	return result;
}
void main()
{
	vec4 finalResult = vec4 (0,0,0,0);
	vec4 uNormal = normalize(frag_Normal);
	vec4 dirToCamera = normalize(u_camera_Postion  - frag_Position);
	//平行光
	finalResult += CalcLightDirectional(lightD,uNormal, dirToCamera);
	//点光
	finalResult += CalcLightPoint(lightP0,uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1,uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2,uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3,uNormal, dirToCamera);
//	// 聚光
	finalResult += CalcLightSpot(lightS,uNormal, dirToCamera);


/*
	float dis = length(u_Light_Postion - frag_Position);

	float attenuation = 1.0 / (light_constant + light_linear * dis + light_quadratic * (dis * dis));

	vec4 light_Dir = normalize(u_Light_Postion - frag_Position);


	//	vec4 light_Dir = u_light_Dir; // for 平行光 方向
	vec4 n = normalize(frag_Normal); //一定 一定 要改成单位向量
	vec4 r = reflect(-light_Dir, n);
	vec4 v = normalize(u_camera_Postion  - frag_Position);


	vec4 Target_ambient =texture(u_texture_Map,frag_UV.xy) * ambinetColor;

	float specularAmount = pow(max(dot(r, v), 0), material_shininess);
	vec4 Target_specular = texture(material_specular,frag_UV.xy) * specularAmount * u_Light_Color;
//	vec4 Target_specular = (material_specular) * specularAmount * u_Light_Color;

	vec4 Target_diffuse = texture(u_texture_Map,frag_UV.xy) * max(dot(light_Dir,n), 0)  * u_Light_Color ;
//	vec4 Target_diffuse =  max(dot(light_Dir,frag_Normal), 0)  * u_Light_Color ;


	float cosTheta = dot( normalize(frag_Position - u_Light_Postion) ,(-1.0f* u_light_Dir) );

	//==========spot light===========//
	float spotRatio;
	if(cosTheta > lightSpot.cosPhyInner){
		//inside
		spotRatio = 1.0f;
	}else if(cosTheta > lightSpot.cosPhyOuter){
		// middle
		spotRatio = 1.0f -( cosTheta - lightSpot.cosPhyInner)/( lightSpot.cosPhyOuter -lightSpot.cosPhyInner );
	}
	else{
		//outside
		spotRatio = 0.0f;
	}
		pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * spotRatio);
*/


	pixel_Colour = finalResult;
//	pixel_Colour = vec4(1.0,1.0,1.0,1.0);


	//	pixel_Colour = objColor * ambinetColor;
//	pixel_Colour =  objColor *(Target_ambient + (Target_diffuse + Target_specular) * attenuation);
}