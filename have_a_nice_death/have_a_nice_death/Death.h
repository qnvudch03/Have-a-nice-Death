#pragma once
#include "LivingObject.h"
#include "InputManager.h"

class Texture;

class Death : public LivingObject
{
	enum EDeathStatepriority
	{
		State_Apear = -1,
		State_Death = 0,
		State_Hitted = 1,
		State_Dash = 2,
		State_AttackUp = 3,
		State_JumptoLand = 4,
		State_JumptoFall = 5,
		State_JumpStart = 6,
		State_Attack1 = 7,
		State_Attack2 = 8,
		State_Attack3 = 9,
		State_Attack4 = 10,

		State_RunToIdle = 11,
		State_RunToUturn = 12,
		State_IdleToRun = 13,
		State_IdleUTurn = 14,
		State_Running = 15,
		State_Idle = 16,

		State_PowerUp = 17,

		State_max
	};

	std::string ConvertDeathStateToString(EDeathStatepriority v) {
		switch (v)
		{

			case EDeathStatepriority::State_Death:        return "Death";
			case EDeathStatepriority::State_Hitted:       return "Hitted";
			case EDeathStatepriority::State_Dash:         return "Dash";
			case EDeathStatepriority::State_JumpStart:    return "JumpStart";
			case EDeathStatepriority::State_JumptoFall:   return "JumpToFalling";
			case EDeathStatepriority::State_JumptoLand:   return "JumpToLand";
			case EDeathStatepriority::State_Attack1:      return "Attack_combo1";
			case EDeathStatepriority::State_Attack2:      return "Attack_combo2";
			case EDeathStatepriority::State_Attack3:      return "Attack_combo3";
			case EDeathStatepriority::State_Attack4:      return "Attack_combo4";
			case EDeathStatepriority::State_RunToIdle:    return "RuntoIdle";
			case EDeathStatepriority::State_RunToUturn:   return "RunUturn";
			case EDeathStatepriority::State_Running:      return "Running";
			case EDeathStatepriority::State_IdleUTurn:    return "IdleUturn";
			case EDeathStatepriority::State_IdleToRun:    return "IdleToRun";
			case EDeathStatepriority::State_Idle:         return "Idle";
			case EDeathStatepriority::State_AttackUp:     return "Attack_up";
			case EDeathStatepriority::State_PowerUp:      return "PowerUp";
			case EDeathStatepriority::State_max:          return "max";
			default: return "Unknown";
		}
	};

	using Super = LivingObject;

public:

	Death(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition)
	{
	}

	~Death() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void OnAnimEnd() override;
	virtual void OnHitBoxSpawn() override;

	virtual void Hitted(HitBox* hitbox) override;

	virtual void UpdateState(KeyType Input) override;

	virtual void TakeDamage(float Damage) override;

	inline bool IsCamMove(EDeathStatepriority state)
	{
		return (((state) < EDeathStatepriority::State_Attack1 && (state) > EDeathStatepriority::State_Dash) ||
					(state) > EDeathStatepriority::State_Attack4);
	}

	bool IsCanJump(EDeathStatepriority state);

	void OnDeathSpawn();

	void CallElevator();

private:
	float deltatime = 0;

	EDeathStatepriority state;
	//std::map<EDeathStatepriority, std::vector<Texture*>*> stateTextureMap;

	//ComboAttack
	int atkcombo = 0;
	float attackStackTimer = 0;

	bool canUpAttack = true;

	bool DashException();
	void LookInputDir();

	bool Attack();

	int CheckDashCondition();
};

