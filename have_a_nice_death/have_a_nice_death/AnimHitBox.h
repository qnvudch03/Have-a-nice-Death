#pragma once
#include "HitBox.h"
#include "Animaotr.h"
#include "Texture.h"

class LivingObject;

class AnimHitBox : public HitBox
{
	using Super = HitBox;

public:

	AnimHitBox(std::vector<Texture*>* animtures)
	{
		animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
		animator.SetAnimTexture(animtures, false);
	}

	~AnimHitBox() = default;


	virtual void Update(float deltatime) override;
	virtual void ClearBox() override;

	void SetAnimHitBox(Vector Pos, Vector Size, float Damage, HitBoxType Type, bool IsPlayerHitBox, LivingObject* Spawner);

	void OnAnimEnd();
	Animator animator;

private:
};

