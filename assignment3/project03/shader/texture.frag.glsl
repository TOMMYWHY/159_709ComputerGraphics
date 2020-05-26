
#version 330 core

in vec4 frag_UV;
in vec4 frag_Normal;
in vec4 frag_Position;

out vec4 pixel_Colour;

uniform vec4 Ia = vec4( 0.3f,0.3f,0.3f,0.0f );
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform vec4 light_postion =  vec4(0.0f, -1.0f, -3.2f, 0.0f);

uniform sampler2D material_diffuse ;
uniform sampler2D material_specular ;
uniform sampler2D material_Normal;
uniform vec4 uni_Ka;
uniform vec4 uni_Kd;
uniform vec4 uni_Ks;
uniform float uni_Ns;
uniform float gamma = 1.2;


void main()
{
	vec4 Ka,Kd,Ks,n;
	if(textureSize(material_diffuse,0).x>0){
		Ka = texture(material_diffuse, frag_UV.xy);
	}else{
		Ka = uni_Ka;
	}
	Kd = uni_Kd;
	if(textureSize(material_specular,0).x > 0){
		Ks = texture(material_specular, frag_UV.xy);
	}else{
		Ks = uni_Kd;
	}


	vec4 uNormal= vec4(normalize(texture(material_Normal, frag_UV.xy).rgb * 2.0f - 1.0f), 0.0f);
	vec4 lightDir = normalize(-light_postion);
	vec4 viewDir    = normalize( - frag_Position);
	vec4 reflectDir = reflect(-lightDir, uNormal);
	vec4 halfwayDir = normalize(lightDir + viewDir);

	// ambient
	vec4 Ta =Ka * Ia;

	// difuse
	float diffIntensity = max(dot( normalize(lightDir )  ,uNormal), 0);
	vec4 Td = diffIntensity * Kd * Id  ;
//	Td = pow(Td,vec4(gamma));

	//specular
//	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0), uni_Ns);
	float specIntensity = pow(max(dot(viewDir, reflectDir), 0), uni_Ns);
	vec4 Ts = specIntensity * Ks *Is ;

	pixel_Colour =(Ta+ Td + Ts) ;// * attenuation;
//	pixel_Colour =(Target_a+ Target_d + Target_s)  * attenuation;

//	pixel_Colour = pow(pixel_Colour,vec4(1.0/gamma));
}