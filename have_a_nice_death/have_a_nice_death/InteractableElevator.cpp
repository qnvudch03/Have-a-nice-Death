#include "pch.h"
#include "InteractableElevator.h"
#include "Game.h"
#include "GameScene.h"
#include "Stage.h"
#include "LivingObject.h"

void InteractableElevator::DoInteract()
{
	readyToInteract = false;

	//플레이어를 엘레베이터 위치로 이동
	LivingObject* player = Game::GetInstance()->GetGameScene()->GetStage()->GetPlayer();

	Vector playerPos = player->GetPos();

	player->SetPos(Vector(GetPos().x, playerPos.y));

	//플레이어 Apeear 애니메이션 뒤로 재생
	player->SetState("Appear", false);
	player->IsActive = false;

	player->animator.SetReversePlay();
	player->animator.StartAnim();
	player->animator.onAnimEnd = [this]() {
		this->ReadyToMove();
		};

	//뒷 애님 종료 후, 엘레베이터 아래로

	//엘레베이터 애님 종료 후, 레벨 로드

}

void InteractableElevator::OnAnimEnd()
{
	if (state == ElevatorState::State_Open)
	{
		readyToInteract = true;
	}

	else if (state == ElevatorState::State_close)
	{
		Game::GetInstance()->GetGameScene()->EraseFromGame(this);

		//메세지 로드, 종료 처리하자
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

	state == ElevatorState::State_close;
}
