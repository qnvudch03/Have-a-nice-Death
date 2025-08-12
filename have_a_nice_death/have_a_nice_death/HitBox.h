#pragma once

class LivingObject;

class HitBox
{
public:
	HitBox(){}
	~HitBox(){}

	void Update(float deltatime);
	void SetHitBox(Vector Pos, Vector Size, float Damage, HitBoxType Type, float LifeTime, bool IsPlayerHitBox, LivingObject* Spawner);
	void ClearBox();

	int GetForwordDirection() { return forwordDirection; }

	Vector GetPos() { return pos; }
	Vector GetSize() { return size; }

	bool isPlayerHitBox = false;
	float damage;

private:

	HitBoxType type;

	Vector pos;
	Vector size;
	float lifeTime;
	float stackTimer = 0;

	LivingObject* spawner = nullptr;
	int forwordDirection = 0;
};

