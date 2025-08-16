#pragma once
#include "InteractableObject.h"
#include "SpriteManager.h"

class InteractableElevator : public InteractableObject
{
	using Super = InteractableObject;

	enum ElevatorState
	{
		State_Open,
		State_close,
		Elevator_Max
	};

public:
	InteractableElevator(RenderLayer rendertype, ImageAnchor drawanchor, Vector pos) : Super(rendertype, drawanchor, pos)
	{
		SetAnimaotrTextures(SpriteManager::GetInstance()->GetTextures("Elevator", "open"), false);

		readyToInteract = true;
		state = ElevatorState::State_Open;
	}

	virtual void DoInteract() override;
	virtual void OnAnimEnd() override;
	virtual void SetDebugMode(bool debugmode) override;

private:
	ElevatorState state = ElevatorState::Elevator_Max;
	void ReadyToMove();
};

