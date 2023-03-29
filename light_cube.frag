#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

in vec3 color;

void main()
{
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	FragColor = vec4(color, 1.0);
	//FragColor = mix(texture(texture1, TexCoord), 
	//				texture(texture2, vec2(TexCoord.x, TexCoord.y)), mixer);
};