
#version 400 core

uniform	vec4	gp;

in	vec2	passVelocity;
in	vec2	passPosition;

out	vec4	outColor;

#define	COLOR_MAX	vec4(1, 1, 1, 0.1)
#define	COLOR_MIN	vec4(1, 0.6, 0.6, 0.1)

void	main()
{
	float	distance = length(gp.xy - passPosition);
	float	ratio = (1 / distance) / 4;

	vec4 color = mix(COLOR_MIN, COLOR_MAX, ratio * gp.w);

	outColor = color;
}
