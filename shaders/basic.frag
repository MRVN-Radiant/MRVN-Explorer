#version 330

in vec3 normal;

out vec4 color;


uniform vec3 base;

void main()
{
	vec3 sun = vec3(0.6f, 0.4f, 0.9f);
	//vec3 base = vec3(0.5f, 0.9f, 0.9f);
	float diffuse = max( dot( normal, sun ), 0.2f );
	vec3 result = diffuse * base;
	// b!scuit gaming
	float z = ( gl_FragCoord.z / gl_FragCoord.w );
	z = min( z / ( 16000 ), 0.3f );
	color = mix(vec4( result, 1.0f ), vec4(1, 1, 1, 1), z);//vec4( result, 1.0f );
}
