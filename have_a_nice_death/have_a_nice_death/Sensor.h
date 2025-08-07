#pragma once

class LivingObject;

class Sensor
{
public:

	bool IsActive()
	{
		return true;
	}

	void Update();

private:
	Vector pos;
	Vector size;

	LivingObject* owner;
};

