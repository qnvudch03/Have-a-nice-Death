#include "pch.h"
#include "TimeManager.h"

int32 TimeManager::TimerIdGenerator = 0;

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU Ŭ��
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	// �ʴ� �����ӷ� ���
	if (_frameTime >= 1.0f)
	{
		_fps = _frameCount;
		_frameTime -= 1.0f;
		_frameCount = 0;
	}

	// Ÿ�̸� ȣ��
	auto Iter = _timers.begin();

	while (Iter != _timers.end())
	{
		if (Iter->Update(_deltaTime))
		{
			Iter = _timers.erase(Iter);
			continue;
		}
		Iter++;
	}
}

void TimeManager::AddTimer(Timer timer)
{
	_timers.push_back(timer);
}

bool Timer::Update(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _interval)
	{
		_func();
		return true;
	}

	return false;
}
