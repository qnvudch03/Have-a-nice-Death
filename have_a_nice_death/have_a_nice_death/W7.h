#pragma once
#include "LivingObject.h"

class W7 : public LivingObject
{
	using Super = LivingObject;

	enum EW7PriorityState
	{
		State_Appear = 0,
		State_Death = 1,
		State_Hitted = 2,

		State_Attack1 = 3,
		State_Attack2 = 4,
		State_Attack3 = 5,
		State_Attack4 = 6,
		State_Attack5 = 7,
		State_Attack6 = 8,

		State_TeleportAppear = 9,
		State_TeleportDisapera = 10,

		State_Running = 11,
		State_Idle = 12,
	};

public:

	W7(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition)
	{

	}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void OnAnimEnd() override;
	virtual void OnHitBoxSpawn() override;
	virtual void Hitted(HitBox* hitbox) override;

	virtual void TakeDamage(float Damage) override;

	virtual void UpdateState(KeyType Input) override;

private:
	float deltatime = 0;

	EW7PriorityState state;
};

