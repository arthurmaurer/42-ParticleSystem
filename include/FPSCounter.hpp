
#pragma once

#include <chrono>
#include <vector>

#define FPS_MAX_TIME_COUNT	60

class FPSCounter
{
public:
	typedef std::chrono::high_resolution_clock::time_point	timePoint;

	struct		KeyTimes
	{
		size_t	oldest;
		size_t	oldest2;
		size_t	oldest3;
		size_t	youngest;
	};

	FPSCounter() = delete;
	~FPSCounter() = delete;

	static float	fps;

	static void		start();
	static void		update();

protected:
	static std::vector<timePoint>	_times;
	static size_t					_timeCount;

	static timePoint	_now();
	static KeyTimes		_getKeyTimes();
	static void			_updateCounter(const KeyTimes & keyTimes);
};

