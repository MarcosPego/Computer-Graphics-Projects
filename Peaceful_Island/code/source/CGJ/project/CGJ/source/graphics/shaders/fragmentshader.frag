#version 330 core

in vec3 Normal;
in vec3 fragPos;
in vec3 cameraPos;
in vec3 toCameraVector;
in vec2 textureCoords;

in float visibility;

uniform vec4 color;
uniform float tiling;

uniform sampler2D mesh_texture;
uniform sampler2D caustics;

out vec4 out_Color;

const float shineDamper = 25.0; // Water
const float reflectivity = 0.3; // Water



uniform float moveFactor;

void main(void)
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	vec3 lightPos = vec3(-40.0f, 40.0f, .0f);

	vec2 texCoords = textureCoords * tiling;

	float ambientStrength = 0.4f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);;
	vec3 diffuse = diff * lightColor;

	vec3 hVector = normalize(normalize(toCameraVector) + normalize( -lightDir));

	vec3 reflectedLight = reflect(hVector, norm);
	float specular = max(dot(reflectedLight, normalize(toCameraVector)), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlight = lightColor * specular * reflectivity;
	
	vec3 result = (ambient + diffuse + specularHighlight);
	

	if (cameraPos.y < 0.0) {
		result = ambient + diffuse + vec3(texture(caustics, vec2(texCoords.x + moveFactor * 6, texCoords.y+moveFactor)));

		out_Color = vec4(result,1)  * texture(mesh_texture, textureCoords) * color;
		out_Color = mix(vec4(0.1,0.3,0.5, 1.0), out_Color, visibility   );
	}
	else {
		out_Color = vec4(result,1)  * texture(mesh_texture, textureCoords) * color;
	}
}