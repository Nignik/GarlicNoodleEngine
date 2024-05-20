#version 330 core
out vec4 FragColor;

uniform float brightness;

void main()
{
	FragColor = vec4(vec3(1.0) * clamp(brightness, 0.0, 1.0), 1.0);
}