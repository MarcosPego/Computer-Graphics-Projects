#version 330 core

layout(location=0) in vec4 in_Position;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

uniform vec4 color;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec4 clipPlane;

out vec3 Normal;
out vec3 fragPos;

out vec2 textureCoords;

out vec3 cameraPos;
out vec3 toCameraVector;

const float density = 0.025;
const float gradient = 0.5;

out float visibility;
	
void main(void)
{	
	
	vec4 worldPosition = ModelMatrix * in_Position;
	vec4 posRelativeToCam = ViewMatrix * worldPosition;
	textureCoords = vec2(in_Position.x/2.0 + 0.5, in_Position.z/2.0 + 0.5);

	gl_ClipDistance[0]= dot(worldPosition, clipPlane);

	gl_Position = ProjectionMatrix * posRelativeToCam;
	
	fragPos = vec3(ModelMatrix * in_Position);
	Normal = mat3(transpose(inverse(ModelMatrix))) * inNormal;


	cameraPos = vec3(inverse(ViewMatrix) * vec4(0,0,0,1));
	toCameraVector = vec3(cameraPos) - worldPosition.xyz;
	
	float distance = length(posRelativeToCam.xyz);
	visibility = exp(-pow(distance*density , gradient ));
	visibility = clamp(visibility, 0.0f, 1.0f);
}