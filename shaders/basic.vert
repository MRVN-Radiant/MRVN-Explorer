#version 130

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 transform;

out vec3 normal;

void main()
{
    gl_Position = transform * vec4( vPos, 1.0f );
    normal = vNormal;
}
