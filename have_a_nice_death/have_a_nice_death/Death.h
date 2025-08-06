#pragma once
#include "LivingObject.h"
#include "InputManager.h"

class Texture;

class Death : public LivingObject
{
	enum EDeathStatepriority
	{
		State_Death = 0,
		State_Hitted = 1,
		State_Dash = 2,
		State_JumpStart = 3,
		State_JumptoFall = 4,
		State_JumptoLand = 5,
		State_Attack1 = 6,
		State_Attack2 = 7,
		State_Attack3 = 8,
		State_Attack4 = 9,

		State_RunToIdle = 10,
		State_RunToUturn = 11,
		State_IdleToRun = 12,
		State_IdleUTurn = 13,
		State_Running = 14,
		State_Idle = 15,

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
			case EDeathStatepriority::State_IdleUTurn:    return "IdealUturn";
			case EDeathStatepriority::State_IdleToRun:    return "IdealToRun";
			case EDeathStatepriority::State_Idle:         return "Ideal";
			case EDeathStatepriority::State_max:          return "max";
			default: return "Unknown";

		}
	};

	using Super = LivingObject;

public:

	Death(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition = ImageAnchor::Topleft)
	{
		SetState("Ideal");
		state = EDeathStatepriority::State_Idle;
		animator.SetAnimSpeed(DefaultAnimSpeed);

		//Setstae¶û Speed °ª ¼³Á¤ÇØ!!
	}

	~Death() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void OnAnimEnd() override;

	void UpdateState(KeyType Input);

private:
	float deltatime = 0;

	EDeathStatepriority state;
	std::map<EDeathStatepriority, std::vector<Texture*>*> stateTextureMap;

	

	//ComboAttack
	int atkcombo = 0;
	float attackStackTimer = 0;

	bool Attack();
};

