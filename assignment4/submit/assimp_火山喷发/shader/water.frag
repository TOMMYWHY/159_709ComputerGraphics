#version 330 core

//in vec4 fragColor;
in vec4 frag_UV;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform sampler2D reflectionTex;
uniform mat4 reflectViewProjection;

uniform vec4 u_camera_Postion; //
//uniform vec4 viewPos; //== u_camera_Postion

uniform vec4 Ia = vec4( 0.4f,0.4f,0.4f,0.0f );
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//uniform vec4 light_postion =  vec4(0.0f, 5.0f, 3.2f, 0.0f);
uniform vec4 light_postion;
//uniform vec4 lightPos;

//uniform vec4 light_postion =  vec4(0.0f, 1.0f, -3.2f, 0.0f);
uniform vec4 material_ambient =  vec4(1.0f, 1.0f, 1.0f, 0.1f);
uniform vec4 kd = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform float time;

//water dir parameters
uniform vec2 waveDirs[]=vec2[](
	vec2(2,-0.3)*0.1,
	vec2(0.2,-0.4)*0.2,
	vec2(-0.3,-0.7)*0.5,
	vec2(0.4,-0.23)*0.1,
	vec2(-0.7,-0.4)*0.4,
	vec2(-0.3,-0.5)*0.3
);

//get water height
float waterHeight(vec3 worldPos)
{
	float h=sin(length(worldPos.x)+time)*0.1;
	float s=1;
	for(int i=0;i<5;++i)
	{
		float s=sin(dot(worldPos.xz*2+time*0.5*length(waveDirs[i])*pow(2,i-1),waveDirs[i]));
		h+=sin(3.14159*s+dot(worldPos.xz*2+time*2*length(waveDirs[i])*pow(2,i-1),waveDirs[i]))*s;
		s*=0.8;
	}
	return h*0.2;
}

//caculate water normal analitically
vec3 calculateWaterNormal(vec3 worldPos)
{
	float dd=0.1;
	float bH=waterHeight(worldPos);
	vec3 u=vec3(dd,waterHeight(worldPos+vec3(dd,0,0))-bH,0);
	vec3 v=vec3(0,waterHeight(worldPos+vec3(0,0,dd))-bH,dd);
	return normalize(cross(v,u));
}

void main()
{
	vec4 Color = vec4(0.1,0.15,0.2,1);
	float ambientStrength = 0.1;
	vec4 ambient = ambientStrength *Ia;

	vec3 frag_Normal=calculateWaterNormal(frag_Position.xyz);

	vec3 norm = normalize(frag_Normal);
//	vec4 norm= (normalize(texture(texture_normal1, frag_UV.xy) * 2.0f - 1.0f));
//	vec3 norm= vec3(normalize(texture(texture_normal1, frag_UV.xy).rgb * 2.0f - 1.0f));

	vec3 lightDir = normalize(light_postion.xyz - frag_Position.xyz);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * Id;

	float specularStrength = 1;
	vec3 viewDir = normalize(u_camera_Postion.xyz - frag_Position.xyz);
	vec3 H = normalize(lightDir+viewDir);
	float spec = pow(max(dot(H, norm), 0.0), 256);
	float specular = specularStrength * spec;

	float fresnel = pow(1-max(dot(norm,viewDir),0),5)*0.1;

	vec3 result = (ambient + diffuse).xyz * Color.xyz +specular+fresnel*Ia.xyz;
	vec4 pp=reflectViewProjection* vec4(frag_Position.xyz,1);
	vec2 reflectionUV=pp.xy/pp.w;

	result+=texture(reflectionTex,reflectionUV*0.5+0.5+norm.xz*0.05).xyz*0.3;

	pixel_Colour = vec4(result,1);
}