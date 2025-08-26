#pragma once
#include "HitBox.h"
#include "Animaotr.h"
#include "Texture.h"

class LivingObject;

class AnimHitBox : public HitBox
{
	using Super = HitBox;

public:

	AnimHitBox() = default;

	~AnimHitBox() = default;


	virtual void Update(float deltatime) override;
	virtual void ClearBox() override;

	void SetAnimHitBox(Vector Pos, Vector Size, std::vector<Texture*>* animtures, float Damage, HitBoxType Type, bool IsPlayerHitBox, LivingObject* Spawner);
	void SetMovingSpeed(Vector speed) { animMovingSpeed = speed; };

	void OnAnimEnd();
	Animator animator;

private:
	Vector animMovingSpeed;
};

