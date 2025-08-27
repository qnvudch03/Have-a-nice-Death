#pragma once
#include "LivingObject.h"

class Texture;
class HitBox;

class MedChost : public LivingObject
{
	enum EMedGhostStatepriority
	{
		State_Appear = 0,
		State_Death = 1,
		State_Hitted1 = 2,
		State_Hitted2 = 3,

		State_Attack1 = 4,
		State_Attack2 = 5,
		State_Attack3 = 6,
		State_Attack4 = 7,

		State_IdleToUturn = 8,
		State_Idle = 9,

		State_max
	};

	std::string ConvertMedGhostStateToString(EMedGhostStatepriority v) {
		switch (v)
		{
		case MedChost::State_Appear:		return "Appear";
		case MedChost::State_Death:			return "Death";
		case MedChost::State_Hitted1:		return "Hitted1";
		case MedChost::State_Hitted2:		return "Hitted2";
		case MedChost::State_Attack1:		return "Attack1";
		case MedChost::State_Attack2:		return "Attack2";
		case MedChost::State_Attack3:		return "Attack3";
		case MedChost::State_Attack4:		return "Attack4";
		case MedChost::State_IdleToUturn:	return "IdleToUTurn";
		case MedChost::State_Idle:			return "Idle";
		default:
			break;
		}
	};

	using Super = LivingObject;

public:

	MedChost(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
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

	EMedGhostStatepriority state;
};

