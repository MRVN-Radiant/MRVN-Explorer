/*
    This file is part of MRVN-Explorer under the MIT license
    Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
*/
#version 330

layout (location = 0) in vec3 layPos;
layout (location = 1) in vec3 layNormal;
layout (location = 2) in vec2 layUV;

uniform mat4 transform;

out vec3 shrNormal;
out vec2 shrUV;

void main()
{
    gl_Position = transform * vec4( layPos, 1.0f );
    shrNormal = layNormal;
    shrUV = layUV;
}
