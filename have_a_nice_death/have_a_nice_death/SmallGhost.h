#pragma once
#include "LivingObject.h"
#include "InputManager.h"

class Texture;
class HitBox;

class SmallGhost : public LivingObject
{
	enum ESmallGhostStatepriority
	{
		State_Appear = 0,
		State_Death = 1,
		State_Hitted1 = 2,
		State_Hitted2 = 3,
		State_Attack = 4,

		State_Running = 5,
		State_Idle = 6,
		State_IdleToUturn = 7,

		State_max
	};

	std::string ConvertSmallGhostStateToString(ESmallGhostStatepriority v) {
		switch (v)
		{

		case SmallGhost::State_Appear:			 return "Appear";
		case SmallGhost::State_Death:			 return "Death";
		case SmallGhost::State_Hitted1:			 return "Hitted1";
		case SmallGhost::State_Hitted2:			 return "Hitted2";
		case SmallGhost::State_Attack:			 return "Attack";
		case SmallGhost::State_Running:			 return "Run";
		case SmallGhost::State_Idle:			 return "Idle";
		case SmallGhost::State_IdleToUturn:      return "IdleTUturn";
		case SmallGhost::State_max:				 return "Unknown";
		default: return "Unknown";
		}
	};

	using Super = LivingObject;

public:

	SmallGhost(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
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

	ESmallGhostStatepriority state;
};

