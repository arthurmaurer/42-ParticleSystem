
#version 400 core

uniform mat4	mvp;

in	vec4	position;

out	vec4	passPosition;

void	main()
{
	gl_Position = vec4(position.xyz, 1) * mvp;
	passPosition = position;
}
