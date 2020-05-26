#version 330 core

in vec4 frag_UV;//texcoords
in vec4 frag_Position;
in vec4 frag_Normal;

uniform vec4 viewPos;
uniform vec4 lightPos;
//= vec4 (0.0f, 2.0f, 0.0f,0.0f) ;
uniform vec4 Ia = vec4(0.2f, 0.2f, 0.2f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

//uniform sampler2D texture_diffuse;
uniform sampler2D material_diffuse ;
uniform sampler2D material_specular ;
uniform sampler2D material_Normal;
uniform float material_shininess = 32.89743616;

uniform vec4 uni_Ka;
uniform vec4 uni_Kd;
uniform vec4 uni_Ks;

out vec4 pixel_Colour;

void main()
{
	vec4 Ka,Kd,Ks,n;
	if(textureSize(material_diffuse,0).x>0){
		 Ka = texture(material_diffuse, frag_UV.xy); //todo
	}else{
		 Ka = uni_Ka;
	}
	 Kd = uni_Kd;

	if(textureSize(material_specular,0).x > 0){
		 Ks = texture(material_specular, frag_UV.xy);
	}else{
		 Ks = uni_Kd;
	}

	if(textureSize(material_Normal,0).x > 0){
		 n= vec4(normalize(texture(material_Normal, frag_UV.xy).rgb * 2.0f - 1.0f), 0.0f);
	}else{
		 n = normalize(frag_Normal);
	}
	vec4 lightDir = normalize(lightPos - frag_Position); //l
	vec4 viewDir = normalize( - frag_Position);
	vec4 reflectDir = reflect(-lightDir, n);

	vec4 Ta = Ia * Ka;
	vec4 Td = Kd* max(dot(n, lightDir), 0.0) * Id;
	vec4 Ts = pow(max(dot(viewDir, reflectDir), 0), material_shininess) *Ks *Is;

	pixel_Colour = Ta + Td + Ts;

}



