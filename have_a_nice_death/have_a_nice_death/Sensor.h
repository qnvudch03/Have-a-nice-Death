#pragma once

class LivingObject;

class Sensor
{
public:

	Sensor(LivingObject* Owner, Vector Size, SensorType SensorType = SensorType::SensorMax) : 
														owner(Owner), size(Size), sensorType(SensorType){}
	~Sensor()
	{
		owner = nullptr;
	}

	bool IsActive()
	{
		return isActive;
	}

	RectanglePos GetRecPos() { return recPos; }

	void Update(Vector textureSize);

private:
	Vector pos;
	Vector size;

	void CheckActive();


	bool isActive = false;

	SensorType sensorType;

	LivingObject* owner;

	RectanglePos recPos;

};

