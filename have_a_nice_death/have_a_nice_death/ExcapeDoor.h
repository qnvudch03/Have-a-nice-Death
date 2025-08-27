#pragma once
#include "InteractableObject.h"
#include "SpriteManager.h"

class ExcapeDoor : public InteractableObject
{
	using Super = InteractableObject;

	enum EDoorState
	{
		State_Open,
		State_close,
		Door_Max
	};

public:
	ExcapeDoor(RenderLayer rendertype, ImageAnchor drawanchor, Vector pos) : Super(rendertype, drawanchor, pos)
	{
		SetAnimaotrTextures(SpriteManager::GetInstance()->GetTextures("Door", "Open"), false);

		readyToInteract = true;
		state = EDoorState::State_Open;
		animator.SetAnimSpeed(20);
		animator.StopAnim();
	}

	virtual void DoInteract() override;
	virtual void OnAnimEnd() override;
	virtual void SetDebugMode(bool debugmode) override;

	void ClearGame();

private:
	EDoorState state = EDoorState::Door_Max;
	void ReadyToClose();
};

