#include "pch.h"
#include "Contractor.h"
#include "Game.h"
#include "GameScene.h"
#include "Object.h"
#include "LivingObject.h"

void Contractor::DoInteract()
{
	if (!readyToInteract)
		return;

	gameScene->SetUI_SelectReword();

	state = contractorState::DisAppear;
	SetState(state, 15);

	player->SetState("PowerUp", false);
	player->animator.SetAnimSpeed(10);

	readyToInteract = false;
}

void Contractor::OnAnimEnd()
{
	if (state == contractorState::Appear)
	{
		state = contractorState::Reading;
		readyToInteract = true;
		SetState(state, 25);
	}

	else if (state == contractorState::Reading)
	{
		state = contractorState::Speaking;

		SetState(state, 25);
	}

	else if (state == contractorState::Speaking)
	{
		state = contractorState::Reading;

		SetState(state, 25);
	}

	else if (state == contractorState::DisAppear)
	{
		state = contractorState::Off;

		SetState(state, 20);
	}

	else if (state == contractorState::Off)
	{
		Game::GetInstance()->GetGameScene()->EraseFromGame(this);
	}

}

void Contractor::SetDebugMode(bool debugmode)
{
	for (auto& Iter : *ownTextures)
	{
		for (auto& iter : Iter.second)
		{
			iter->SetDrawBound(debugmode);
		}
	}
}

void Contractor::RemoteDisApear()
{
	state = contractorState::DisAppear;
	SetState(state, 15);

	readyToInteract = false;
}

void Contractor::SetState(contractorState state, float animSpeed)
{
	animator.ResetAnimTimer(animSpeed);
	SetAnimaotrTextures(&(*ownTextures)[ConvertContractorStateToString(state)], false);
}
