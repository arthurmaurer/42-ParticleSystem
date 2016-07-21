
#include <iostream>
#include <algorithm>

#include "FPSCounter.hpp"
#include "Utils.hpp"

float				FPSCounter::fps;
std::vector<float>	FPSCounter::_ticks;

void	FPSCounter::tick(float time)
{
	_ticks.push_back(time);

	_updateFPS();
}

void	FPSCounter::_removeOldTicks()
{
	size_t		i = 0;
	const float	limit = Utils::getTime() - 1.f;

	for (const float tick : _ticks)
	{
		if (tick >= limit)
			break;

		++i;
	}

	const auto	begin = _ticks.begin();

	_ticks.erase(begin, begin + i);
}

void	FPSCounter::_updateFPS()
{
	_removeOldTicks();

	fps = (float)_ticks.size();
}