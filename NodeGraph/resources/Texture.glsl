#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

layout (location = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord);
}
