#pragma once
class HitBox
{
public:
	HitBox(){}
	~HitBox(){}

	void Update(float deltatime);
	void SetHitBox(Vector Pos, Vector Size, HitBoxType Type, float LifeTime);
	void ClearBox();

	Vector GetPos() { return pos; }
	Vector GetSize() { return size; }

private:

	HitBoxType type;

	Vector pos;
	Vector size;
	float lifeTime;
	float stackTimer = 0;
};

