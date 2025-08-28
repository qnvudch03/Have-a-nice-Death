#pragma once
#include "LivingObject.h"

class Texture;
class HitBox;

class Nurse : public LivingObject
{
	using Super = LivingObject;

	enum ENurseStatepriority
	{
		State_Appear = 0,
		State_Death = 1,
		State_Hitted1 = 2,
		State_Hitted2 = 3,

		State_Run = 4,
		State_Teleport_Disappear = 5,
		State_Teleport_Appear = 6,

		State_Attack1 = 7,
		State_Attack2 = 8,

		State_Idle = 9,
		State_IdleToUturn = 10,

		State_max
	};

	std::string ConvertPillStateToString(ENurseStatepriority v) {
		switch (v)
		{
		case Nurse::State_Appear:					return "Appear";
		case Nurse::State_Death:					return "Death";
		case Nurse::State_Hitted1:					return "Hitted1";
		case Nurse::State_Hitted2:					return "Hitted2";
		case Nurse::State_Run:						return "Run";
		case Nurse::State_Teleport_Disappear:		return "Teleport_disappear";
		case Nurse::State_Teleport_Appear:			return "Telepport_Appear";
		case Nurse::State_Attack1:					return "Attack01";
		case Nurse::State_Attack2:					return "Attack02";
		case Nurse::State_Idle:						return "Idle";
		case Nurse::State_IdleToUturn:				return "IdleToUturn";
		case Nurse::State_max:
			break;
		default:
			break;
		}
	};

public:
	Nurse(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
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
	LivingObject* LookEnemy();

	void TeleportToTarget();

	ENurseStatepriority state;

};

