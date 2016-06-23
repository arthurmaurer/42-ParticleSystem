
#version 400 core

uniform	mat4	mvp;

in	vec4	inPosition;
in	vec4	inVelocity;

out	vec3	passPosition;

void	main()
{
	gl_Position = vec4(inPosition.xyz, 1) * mvp;
	passPosition = inPosition.xyz;
}
