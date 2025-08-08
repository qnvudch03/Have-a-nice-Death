#pragma once

class Sensor;
class Collider;
class HitBox;

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

	void ReservedHitBox(HitBox* hitBox)
	{
		hitBoxVec.push_back(hitBox);
	}

	void DrawReserved();

	void DrawRenctangle(Vector TopLeftPos, Vector BootomRightPos, D2D1::ColorF color, float Linewidth = 2.0f);

private:
	std::vector<Sensor*> sensorVec;
	std::vector<Collider* > colliderVec;
	std::vector< HitBox*> hitBoxVec;
	ID2D1RenderTarget* renderTarget = nullptr;
};

