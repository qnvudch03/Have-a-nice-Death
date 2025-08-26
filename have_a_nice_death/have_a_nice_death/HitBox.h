#pragma once

class LivingObject;

class HitBox
{
public:
	HitBox(){}
	virtual ~HitBox(){}

	virtual void Update(float deltatime);
	void SetHitBox(Vector Pos, Vector Size, float Damage, HitBoxType Type, float LifeTime, bool IsPlayerHitBox, LivingObject* Spawner);
	virtual void ClearBox();

	int GetForwordDirection() { return forwordDirection; }

	Vector GetPos() { return pos; }
	Vector GetSize() { return size; }


	void SetCollition() { collision = true; }
	void DisableCollition() { collision = false; }
	bool GetIsCollide() { return collision; }
	ImageAnchor hitBoxAncor = ImageAnchor::Center;

	bool isPlayerHitBox = false;
	float damage;

protected:

	HitBoxType type;

	bool collision = true;
	Vector pos;
	Vector size;
	float lifeTime;
	float stackTimer = 0;

	LivingObject* spawner = nullptr;
	int forwordDirection = 0;
};

