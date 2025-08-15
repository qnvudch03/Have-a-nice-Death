#pragma once

class Sensor;
class Collider;
class HitBox;
class Object;

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

	/*void ReservedobjByTexture(Object* obj)
	{
		objVec.push_back(obj);
	}*/

	void DrawReserved();

	void DrawRenctangle(Vector TopLeftPos, Vector BootomRightPos, D2D1::ColorF color, float Linewidth = 2.0f);

private:
	std::vector<Sensor*> sensorVec;
	std::vector<Collider* > colliderVec;
	std::vector< HitBox*> hitBoxVec;
	//std::vector< Object*> objVec;

	ID2D1RenderTarget* renderTarget = nullptr;
};

