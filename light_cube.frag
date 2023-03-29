#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

uniform vec3 eyePos;
uniform vec3 lightDir;
vec3 lightPos = vec3(-500.0, 0.0, 0.0);

in vec3 normal;
in vec3 position;

float directionalLight(vec3 lightDir, vec3 normal) {
    float f = dot(normalize(normal), -lightDir);
    if (f > 0)
        return f;
    else
        return 0.0;
}

float pointLight(vec3 lightPos, vec3 normal, vec3 position) {
    vec3 lightDelta = position - lightPos;
    vec3 lightDir = normalize(lightDelta);

    return directionalLight(lightDir, normal);

    // fajne rzeczy
    // vec3 distance = length(lightDelta);
    //  float attenuation = 0.1 * distance + 0.001 * distance * distance;
    // return directionalLight(lightDir, normal) / attenuation;
}

float specularLight(vec3 lightPos, vec3 normal, vec3 position, vec3 eyePos, float shininess) {
    vec3 lightDelta = position - lightPos;
    vec3 lightDir = normalize(lightDelta);

    float f = dot(normalize(normal), -lightDir);
    if (f < 0)
        return 0.0;

    vec3 viewDir = -normalize(eyePos - position);
    vec3 reflectDir = reflect(-lightDir, normal);

    float s = pow(
        max(0.0, dot(viewDir, reflectDir)),
        shininess
    );
    return s;
}

void main()
{
    float light = directionalLight(lightDir, normal);
    vec3 color = vec3(light, 0.0, 0.0);

    float light2 = pointLight(lightPos, normal, position);
    vec3 color2 = vec3(0.0, light2, 0.0);

    float light3 = specularLight(lightPos, normal, position, eyePos, 256.0);
    vec3 color3 = vec3(light3, light3, light3);

	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	FragColor = vec4(color3 + color2 * 0.5, 1.0);
	//FragColor = mix(texture(texture1, TexCoord), 
	//				texture(texture2, vec2(TexCoord.x, TexCoord.y)), mixer);
};