/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#version 330

in vec3 shrNormal;
in vec2 shrUV;

out vec4 outColor;


uniform sampler2D CurrentTexture;

void main()
{
	vec3 sun = vec3(0.6f, 0.4f, 0.9f);
	vec3 v3Base = vec3(0.5f, 0.9f, 0.9f);
	float diffuse = max( dot( shrNormal, sun ), 0.2f );
	vec3 result = diffuse * vec3( texture(CurrentTexture, shrUV) );
	// b!scuit gaming
	float z = ( gl_FragCoord.z / gl_FragCoord.w );
	z = min( z / ( 16000 ), 0.3f );

	// test
	//outColor = texture(CurrentTexture, shrUV);
	outColor = mix(vec4( result, 1.0f ), vec4(1, 1, 1, 1), z);//vec4( result, 1.0f );
}
