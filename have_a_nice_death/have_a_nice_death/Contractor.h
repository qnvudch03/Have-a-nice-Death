#pragma once
#include "InteractableObject.h"
#include "SpriteManager.h"

class Contractor : public InteractableObject
{
	using Super = InteractableObject;

	enum contractorState
	{
		Appear = 0,
		Reading = 1,
		Speaking = 2,
		DisAppear = 3,
		Off = 4,
		contractor_Max
	};

	std::string ConvertContractorStateToString(contractorState v)
	{
		switch (v)
		{
		case Contractor::Appear:	return "Appear";
		case Contractor::Reading:	return "Reading";
		case Contractor::Speaking:	return "Speaking";
		case Contractor::DisAppear:	return "DisAppear";
		case Contractor::Off:		return "Off";
		case Contractor::contractor_Max:	return "MAX";
		default: return "MAX";
		}
	}

public:
	Contractor(RenderLayer rendertype, ImageAnchor drawanchor, Vector pos) : Super(rendertype, drawanchor, pos)
	{
		ownTextures = SpriteManager::GetInstance()->GetTextureMap("Contractor");
		state = contractorState::Appear;
		SetAnimaotrTextures(&(*ownTextures)[ConvertContractorStateToString(state)], false);

		readyToInteract = true;
	}

	virtual void DoInteract() override;
	virtual void OnAnimEnd() override;
	virtual void SetDebugMode(bool debugmode) override;

	void SetState(contractorState state, float animSpeed);

private:
	contractorState state = contractorState::contractor_Max;
	std::map<std::string, std::vector<Texture*>>* ownTextures = nullptr;
};

