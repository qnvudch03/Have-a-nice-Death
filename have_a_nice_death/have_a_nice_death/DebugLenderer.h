#pragma once

class Sensor;
class Collider;

class DebugLenderer
{
public:
	DebugLenderer(ID2D1RenderTarget* RenderTarget) : renderTarget(RenderTarget){}

	void ReserveSensor(Sensor* Sensor)
	{
		sensorVec.push_back(Sensor);
	}

	void ReserveCollider(Collider* Collider)
	{
		colliderVec.push_back(Collider);
	}

	void DrawReserved();

	void DrawRenctangle(Vector TopLeftPos, Vector BootomRightPos, D2D1::ColorF color, float Linewidth = 2.0f);

private:
	std::vector<Sensor*> sensorVec;
	std::vector<Collider* > colliderVec;
	ID2D1RenderTarget* renderTarget = nullptr;
};

