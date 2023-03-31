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
	// Calculate diffuse lighting + texture
	vec3 v3Sun = vec3(0.6f, 0.4f, 0.9f);
	float diffuse = max( dot( shrNormal, v3Sun ), 0.2f );
	vec3 v3Result = diffuse * vec3( texture(CurrentTexture, shrUV) );

	// b!scuit gaming
	float fFog = ( gl_FragCoord.z / gl_FragCoord.w );
	fFog = min( fFog / ( 16000 ), 0.3f );

	outColor = mix(vec4( v3Result, 1.0f ), vec4(1, 1, 1, 1), fFog);
}
