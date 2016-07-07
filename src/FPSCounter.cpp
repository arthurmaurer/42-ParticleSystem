
#include <iostream>

#include "FPSCounter.hpp"

float								FPSCounter::fps = 0;
size_t								FPSCounter::_timeCount = 0;
std::vector<FPSCounter::timePoint>	FPSCounter::_times;

void		FPSCounter::start()
{
	_times.resize(FPS_MAX_TIME_COUNT);
	_timeCount = 0;
}

void		FPSCounter::update()
{
	KeyTimes	keyTimes = _getKeyTimes();

	if (_timeCount < FPS_MAX_TIME_COUNT)
	{
		_times[_timeCount] = _now();
		++_timeCount;
	}
	else
	{
		_times[keyTimes.oldest] = _now();

		keyTimes.youngest = keyTimes.oldest;
		keyTimes.oldest = keyTimes.oldest2;
		keyTimes.oldest2 = keyTimes.oldest3;
	}

	_updateCounter(keyTimes);
}

FPSCounter::timePoint	FPSCounter::_now()
{
	return std::chrono::high_resolution_clock::now();
}

FPSCounter::KeyTimes	FPSCounter::_getKeyTimes()
{
	KeyTimes	keyTimes = { 0, 0, 0, 0 };
	timePoint	oldest = timePoint::max();
	timePoint	oldest2 = timePoint::max();
	timePoint	youngest = timePoint::min();

	for (size_t i = 0; i < _timeCount; ++i)
	{
		const timePoint &	time = _times[i];

		if (time > youngest)
		{
			youngest = time;
			keyTimes.youngest = i;
		}
		else if (time < oldest)
		{
			oldest2 = oldest;
			oldest = time;
			keyTimes.oldest2 = keyTimes.oldest;
			keyTimes.oldest = i;
		}
		else if (time < oldest2)
		{
			oldest2 = time;
			keyTimes.oldest2 = i;
		}
	}

	return keyTimes;
}

void					FPSCounter::_updateCounter(const KeyTimes & keyTimes)
{
	std::chrono::duration<float, std::milli>	duration = _times[keyTimes.youngest] - _times[keyTimes.oldest];

	fps = _timeCount / static_cast<float>(duration.count()) * 1000;
}
