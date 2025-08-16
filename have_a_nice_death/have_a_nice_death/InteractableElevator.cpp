#include "pch.h"
#include "InteractableElevator.h"
#include "Game.h"
#include "GameScene.h"
#include "Stage.h"
#include "LivingObject.h"

void InteractableElevator::DoInteract()
{
	readyToInteract = false;

	//�÷��̾ ���������� ��ġ�� �̵�
	LivingObject* player = Game::GetInstance()->GetGameScene()->GetStage()->GetPlayer();

	Vector playerPos = player->GetPos();

	player->SetPos(Vector(GetPos().x, playerPos.y));

	//�÷��̾� Apeear �ִϸ��̼� �ڷ� ���
	player->SetState("Appear", false);
	player->IsActive = false;

	player->animator.SetReversePlay();
	player->animator.StartAnim();
	player->animator.onAnimEnd = [this]() {
		this->ReadyToMove();
		};

	//�� �ִ� ���� ��, ���������� �Ʒ���

	//���������� �ִ� ���� ��, ���� �ε�

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

		//�޼��� �ε�, ���� ó������
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
