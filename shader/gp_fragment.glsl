
#version 400 core

in	vec4	passPosition;

out vec4	outColor;

void	main()
{
	if (passPosition.w != 0)
		outColor = vec4(1, 0, 0, 1);
	else
		outColor = vec4(0, 1, 0, 0);
}
