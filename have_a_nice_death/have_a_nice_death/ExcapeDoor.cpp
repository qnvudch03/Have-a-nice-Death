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
		//�÷��̾ ���������� ��ġ�� �̵�

		Vector playerPos = player->GetPos();

		player->SetPos(Vector(GetPos().x, playerPos.y));

		//�÷��̾� Apeear �ִϸ��̼� �ڷ� ���
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
