#pragma once
#include "LivingObject.h"

class Texture;
class HitBox;

class Pill : public LivingObject
{

	using Super = LivingObject;

	enum EPillStatepriority
	{
		State_Appear = 0,
		State_Death = 1,
		State_Hitted = 2,

		State_Attack1_start = 3,
		State_Attack1 = 4,
		State_Attack1_end = 5,
		State_Attack2 = 6,

		State_Idle = 7,
		State_IdleToUturn = 8,

		State_max
	};

	std::string ConvertPillStateToString(EPillStatepriority v) {
		switch (v)
		{
		case Pill::State_Appear:			return "Appear";
		case Pill::State_Death:				return "Death";
		case Pill::State_Hitted:			return "Hitted";
		case Pill::State_Attack1_start:		return "Attack1_start";
		case Pill::State_Attack1:			return "Attack1";
		case Pill::State_Attack1_end:		return "Attack1_end";
		case Pill::State_Attack2:			return "Attack2";
		case Pill::State_Idle:				return "Idle";
		case Pill::State_IdleToUturn:		return "IdleToUturn";
		default:
			break;
		}
	};

public:
	Pill(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition)
	{

	}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void OnAnimEnd() override;
	virtual void AnimCallBack() override;
	virtual void Hitted(HitBox* hitbox) override;

	virtual void TakeDamage(float Damage) override;

	virtual void UpdateState(KeyType Input) override;

private:
	float deltatime = 0;

	EPillStatepriority state;
};

