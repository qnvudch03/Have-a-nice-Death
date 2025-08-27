#include "pch.h"
#include "ExcapeDoor.h"
#include "GameScene.h"
#include "TimeManager.h"
#include "Game.h"
#include "LivingObject.h"

void ExcapeDoor::DoInteract()
{
	readyToInteract = false;
	animator.StartAnim();

	
}

void ExcapeDoor::OnAnimEnd()
{
	if (state == EDoorState::State_Open)
	{
		//플레이어를 엘레베이터 위치로 이동

		Vector playerPos = player->GetPos();

		player->SetPos(Vector(GetPos().x, playerPos.y));

		//플레이어 Apeear 애니메이션 뒤로 재생
		player->SetSingleCallbackState("GameEnd", false);
		player->animator.SetAnimSpeed(20);
		player->IsActive = false;
		player->animator.StartAnim();

		player->animator.onAnimEnd = [this]() {this->ReadyToClose(); };
	}

	else if (state == EDoorState::State_close)
	{
		//Game::GetInstance()->GetGameScene()->EraseFromGame(this);
		gameScene->EraseFromGame(this);
		Game::GetInstance()->GetGameScene()->SetUI_ClearGame();

	}
}

void ExcapeDoor::SetDebugMode(bool debugmode)
{
}

void ExcapeDoor::ReadyToClose()
{
	animator.SetReversePlay();
	animator.StartAnim();
	state = EDoorState::State_close;

}
