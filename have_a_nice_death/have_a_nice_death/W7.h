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

	std::string ConvertW7StateToString(EW7PriorityState v) {
		switch (v)
		{
		case W7::State_Appear:					return "Appear";
		case W7::State_Death:					return "Death";
		case W7::State_Hitted:					return "Hitted";
		case W7::State_Attack1:					return "Attack1";
		case W7::State_Attack2:					return "Attack2";
		case W7::State_Attack3:					return "Attack3";
		case W7::State_Attack4:					return "Attack4";
		case W7::State_Attack5:					return "Attack5";
		case W7::State_Attack6:					return "Attack6";
		case W7::State_TeleportAppear:			return "Teleport_Appear";
		case W7::State_TeleportDisapera:		return "Teleport_Disappear";
		case W7::State_Running:					return "Run";
		case W7::State_Idle:					return "Idle";
			break;
		default:
			break;
		}
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
	virtual void AnimCallBack() override;
	virtual void Hitted(HitBox* hitbox) override;

	virtual void TakeDamage(float Damage) override;

	virtual void UpdateState(KeyType Input) override;

	void TeleportMapBound();

private:
	float deltatime = 0;
	std::vector<float>& ShuffleVector(std::vector<float>& vec);

	Vector flyingTargetPos;
	Vector flyingStartPos;

	LivingObject* LookEnemy();

	float moveCounter = 0;
	bool readyAtk4 = false;

	EW7PriorityState state;

};

