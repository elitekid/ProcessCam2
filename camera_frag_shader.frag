#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureID_bg;

void main()
{
	FragColor = texture(textureID_bg, TexCoord);
}