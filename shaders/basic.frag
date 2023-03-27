/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#version 330

in vec3 normal;
in vec2 uv;

out vec4 color;


uniform sampler2D CurrentTexture;

void main()
{
	vec3 sun = vec3(0.6f, 0.4f, 0.9f);
	//vec3 base = vec3(0.5f, 0.9f, 0.9f);
	float diffuse = max( dot( normal, sun ), 0.2f );
	vec3 result = diffuse * vec3( texture(CurrentTexture, uv) );
	// b!scuit gaming
	float z = ( gl_FragCoord.z / gl_FragCoord.w );
	z = min( z / ( 16000 ), 0.3f );
	//color = mix(vec4( result, 1.0f ), vec4(1, 1, 1, 1), z);//vec4( result, 1.0f );
	color = texture(CurrentTexture, uv);
	//color = mix(vec4( result, 1.0f ), vec4(1, 1, 1, 1), z);//vec4( result, 1.0f );
}
