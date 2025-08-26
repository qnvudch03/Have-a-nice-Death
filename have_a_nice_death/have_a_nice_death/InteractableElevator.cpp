#include "pch.h"
#include "InteractableElevator.h"
#include "Game.h"
#include "GameScene.h"
#include "Stage.h"
#include "LivingObject.h"
#include "TimeManager.h"
#include "Contractor.h"

void InteractableElevator::DoInteract()
{
	readyToInteract = false;

	//플레이어를 엘레베이터 위치로 이동

	Vector playerPos = player->GetPos();

	player->SetPos(Vector(GetPos().x, playerPos.y));

	//플레이어 Apeear 애니메이션 뒤로 재생
	player->SetSingleCallbackState("Appear", false);
	player->animator.SetAnimSpeed(25);
	player->IsActive = false;

	player->animator.SetReversePlay();
	player->animator.StartAnim();
	player->animator.onAnimEnd = [this]() {
		this->ReadyToMove();
		};

	auto contracot = gameScene->GetStage()->GetContractor();

	if (contracot->GetReadyToInteract() == true)
	{
		contracot->RemoteDisApear();
	}

}

void InteractableElevator::OnAnimEnd()
{
	if (state == ElevatorState::State_Open)
	{
		readyToInteract = true;
	}

	else if (state == ElevatorState::State_close)
	{
		//Game::GetInstance()->GetGameScene()->EraseFromGame(this);
		gameScene->EraseFromGame(this);
		gameScene->SavePlayData();

		//메세지 로드, 종료 처리하자
		TimeManager::GetInstance()->AddTimer(Timer([this]() 
			{
				Game::GetInstance()->GetGameScene()->GoNextStage();
			}
		, 0.5));
		
	}
	
}

void InteractableElevator::SetDebugMode(bool debugmode)
{
	for (auto& Iter : *(animator.GetAnimTextureVec()))
	{
		Iter->SetDrawBound(debugmode);
	}
}

void InteractableElevator::ReadyToMove()
{
	animator.SetReversePlay();
	animator.StartAnim();

	state = ElevatorState::State_close;
}
