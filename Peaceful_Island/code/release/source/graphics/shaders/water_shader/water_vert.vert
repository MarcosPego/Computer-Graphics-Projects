#version 330 core

layout(location=0) in vec4 in_Position;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

out vec2 textureCoords;
out vec4 worldPosition;


out vec3 toReflectCameraVector;
out vec3 toCameraVector;


out vec4 clipSpace;

uniform mat4 ReflectedViewMatrix;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 Normal;
out vec3 fragPos;

const float tiling = 2.0f;

out vec3 TexCoords;
out vec3 cameraPos;
out float visibility;

const float density = 0.01;
const float gradient = 1.0;

void main(void) {

	vec4 pos = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	TexCoords = vec3(in_Position);
	worldPosition = ModelMatrix * pos  ;
	vec4 posRelativeToCam = ViewMatrix * worldPosition;
	textureCoords = vec2(in_Position.x/2.0 + 0.5, in_Position.z/2.0 + 0.5) * tiling;

	clipSpace = ProjectionMatrix * posRelativeToCam;
	gl_Position = clipSpace;


	vec3 cameraReflectPos =  vec3(inverse(ViewMatrix) * vec4(0,0,0,1));
	toReflectCameraVector =  vec3(cameraReflectPos) - worldPosition.xyz;
	
	cameraPos = vec3(inverse(ViewMatrix) * vec4(0,0,0,1));
	toCameraVector = vec3(cameraPos) - worldPosition.xyz;
	
	Normal = inNormal;

	fragPos = vec3(ModelMatrix * in_Position);
	
	float distance = length(posRelativeToCam.xyz);
	visibility = exp(-pow(distance*density , gradient ));
	visibility = clamp(visibility, 0.0f, 1.0f);
}