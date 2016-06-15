
#version 400 core

in	vec2	inPosition;
in	vec2	inVelocity;

out	vec2	passVelocity;
out	vec2	passPosition;

void	main()
{
	gl_Position = vec4(inPosition, 0, 1);
	passVelocity = inVelocity;
	passPosition = inPosition;
}
