
#pragma once

#include <chrono>
#include <vector>

class FPSCounter
{
protected:
	static std::vector<float>	_ticks;

public:
	static float	fps;

	static void	tick(float time);

protected:
	static void	_removeOldTicks();
	static void	_updateFPS();
};

