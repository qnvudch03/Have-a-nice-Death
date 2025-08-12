#pragma once
#include "Singleton.h"

class Timer
{
public:
	using TimerFunc = std::function<void()>;
	Timer() = default;
	Timer(TimerFunc func, float armTime) : _func(func), _interval(armTime) {}
	bool Update(float deltaTime);
	int32 id = 0;

private:
	TimerFunc _func;
	float _sumTime = 0;
	float _interval = 0;
};

class TimeManager : public Singleton<TimeManager>
{
public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	static float GetDeltaTime() { if (GetInstance()) return GetInstance()->_deltaTime; return 0; }

	void AddTimer(Timer timer);
	void Remove(int32 id);

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.f;

private:
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;

	static int32 TimerIdGenerator;
	std::vector<Timer> _timers;
};

