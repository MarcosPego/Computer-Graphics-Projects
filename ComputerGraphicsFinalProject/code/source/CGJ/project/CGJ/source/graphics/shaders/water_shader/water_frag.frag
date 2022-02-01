#version 330 core

const float Eta = pow((1.0-1.3),2)/(1.0 + 1.3); // Water



const float shineDamper = 20.0; // Water
const float reflectivity = 0.3; // Water

in vec2 textureCoords;
in vec3 Normal;
in vec3 toCameraVector;
in vec3 toReflectCameraVector;
in vec4 clipSpace;

in vec3 fragPos;
in vec3 cameraPos;
in float visibility;

uniform vec4 color;



out vec4 out_Color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudv;
uniform sampler2D dudv_n;
uniform sampler2D depth_map;

uniform float moveFactor;



const float waveStrength = 0.05;

void main(void) {
	vec3 vlightPos = vec3(-40.0f, 40.0f, 0.0f);


	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;

	vec2 refractTexCoords = vec2(ndc);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);


	float near = 0.1f;
	float far = 1000.0f;
	float depth = texture(depth_map, refractTexCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * ( far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * ( far - near));

	float waterDepth = floorDistance - waterDistance;


	vec2 distortedTexCoords = texture(dudv, vec2(textureCoords.x + moveFactor * 6, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
	vec2 totaldistortion = (texture(dudv, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength *clamp(waterDepth/5.0, 0.0, 1.0);

	refractTexCoords += totaldistortion;
	reflectTexCoords += totaldistortion;

	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
	vec4 refractColour = texture(refractionTexture, refractTexCoords);

	
	vec3 lightDir = normalize(vlightPos - fragPos);

	vec3 hVector = normalize(normalize(toCameraVector) + normalize(  -lightDir));

	float fresnel = Eta + (1.0 - Eta) * pow(1.0 - max(0.0, dot(normalize(toCameraVector), normalize(Normal) )), 5.0);
	

	vec4 normalMapColor = texture(dudv_n, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b,  normalMapColor.g * 2.0 - 1.0  );
	normal = normalize(normal);


	vec3 reflectedLight = reflect(normalize(hVector), normal);
	float specular = max(dot(reflectedLight, normalize(toCameraVector)), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlight = vec3(1.0, 1.0, 1.0) * specular * reflectivity * clamp(waterDepth/5.0, 0.0, 1.0);


	if(cameraPos.y < 0 ){
		out_Color = mix(refractColour, reflectColour, fresnel);
		out_Color = mix(vec4(0.1,0.3,0.5, 1.0), out_Color, visibility   );;
	}
	else{
		out_Color = mix(refractColour, reflectColour, fresnel);
		out_Color = mix(out_Color, vec4(0.1,0.3,0.5,1.0), 0.2) + vec4(specularHighlight, 0.0);
		out_Color.a = clamp(waterDepth/5.0, 0.0, 1.0);
	}


}