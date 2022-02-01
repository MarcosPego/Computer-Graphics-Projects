#version 330 core
layout (location = 0) in vec4 in_Position;

out vec3 TexCoords;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	vec4 worldPosition = in_Position;
    TexCoords = vec3(in_Position);
    vec4 pos = ProjectionMatrix * ViewMatrix * worldPosition;
    gl_Position = pos.xyww;
} 

