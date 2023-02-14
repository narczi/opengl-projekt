#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), 
					texture(texture2, vec2(TexCoord.x, TexCoord.y)), mixer);
};