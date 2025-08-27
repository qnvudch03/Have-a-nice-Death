#include "pch.h"
#include "MedChost.h"
#include "HitBoxManager.h"
#include "SpriteManager.h"
#include "HitBox.h"
#include "Controller.h"
#include "Game.h"
#include "DebugLenderer.h"

void MedChost::Init()
{
	Super::Init();

	SetSingleCallbackState("Appear", false);
	state = EMedGhostStatepriority::State_Appear;
	animator.SetAnimSpeed(20);

	SETTRIPLE(false)

	//체 최대체력 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워 
	SetStat(ObjectStat(100, 100, 17, 7, 0, 100, 7, 900));

	SetDetectRnage(700);
	GetController()->SetAttackNum(4);
}

void MedChost::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == EMedGhostStatepriority::State_Appear)
		return;

	UpdateState(Super::GetController()->GetInput());
}

void MedChost::Destroy()
{
	Super::Destroy();
}

void MedChost::OnAnimEnd()
{
	if (!IsActive)
	{
		Die();
	}

	if (state == EMedGhostStatepriority::State_Appear)
	{
		SETTRIPLE(true)
	}

	else if (state == EMedGhostStatepriority::State_IdleToUturn)
	{
		isTurning = false;
		forwordDirection *= -1;
		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
	}

	else if (state == EMedGhostStatepriority::State_Attack1 ||
			state == EMedGhostStatepriority::State_Attack2 ||
			state == EMedGhostStatepriority::State_Attack3 ||
			state == EMedGhostStatepriority::State_Attack4)
	{
		isCanMove = true;
		isCanJump = true;
	}

	SetSingleCallbackState("Idle", true);
	state = EMedGhostStatepriority::State_Idle;
	animator.SetAnimSpeed(10);
}

void MedChost::AnimCallBack()
{
	if (state != EMedGhostStatepriority::State_Attack1 &&
		state != EMedGhostStatepriority::State_Attack2 &&
		state != EMedGhostStatepriority::State_Attack3 &&
		state != EMedGhostStatepriority::State_Attack4)

		return;

	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	HitBox* hitbox = hitBoxManager->CallHitBox();
	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };

	switch (state)
	{
	case MedChost::State_Attack1:
		colliderCenterPos.x += 100 * forwordDirection;
		colliderCenterPos.y += 40;
		hitBoxSize.x = 120;
		hitBoxSize.y = 120;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.7, HitBoxType::Fixed, 0.2, GetController()->isPlayerController, this);
		break;

	case MedChost::State_Attack2:
		colliderCenterPos.x += 20 * forwordDirection;
		colliderCenterPos.y -= 100;
		hitBoxSize.x = 150;
		hitBoxSize.y = 100;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.2, HitBoxType::Fixed, 0.2, GetController()->isPlayerController, this);
		break;

	case MedChost::State_Attack3:
		colliderCenterPos.x += 50 * forwordDirection;
		colliderCenterPos.y -= 60;
		hitBoxSize.x = 150;
		hitBoxSize.y = 200;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 2.0, HitBoxType::Fixed, 0.2, GetController()->isPlayerController, this);
		break;

	case MedChost::State_Attack4:
		colliderCenterPos.x += 0 * forwordDirection;
		colliderCenterPos.y -= 0;
		hitBoxSize.x = 300;
		hitBoxSize.y = 100;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.2, HitBoxType::Fixed, 0.5, GetController()->isPlayerController, this);
		break;

	default:
		break;
	}

	if (hitbox)
	{
		hitBoxManager->AddHitBox(hitbox);

		Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(hitbox);
	}
		

}
void MedChost::Hitted(HitBox* hitbox)
{
	if (!DamagedAble || !IsActive)
		return;

	Super::Hitted(hitbox);
}

void MedChost::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{

		if (state == EMedGhostStatepriority::State_Hitted1 ||
			state == EMedGhostStatepriority::State_Hitted2)
		{
			animator.ResetAnimTimer(20);
			SetSingleCallbackState("Hitted2", false);
			state = EMedGhostStatepriority::State_Hitted2;
		}

		else
		{
			animator.ResetAnimTimer(20);
			SetSingleCallbackState("Hitted1", false);
			state = EMedGhostStatepriority::State_Hitted1;
		}
	}

	else
	{
		state = EMedGhostStatepriority::State_Death;
	}
}

void MedChost::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;


	if (state == EMedGhostStatepriority::State_Hitted1 ||
		state == EMedGhostStatepriority::State_Hitted2 ||
		state == EMedGhostStatepriority::State_IdleToUturn ||
		state == EMedGhostStatepriority::State_Attack1 ||
		state == EMedGhostStatepriority::State_Attack2 ||
		state == EMedGhostStatepriority::State_Attack3 ||
		state == EMedGhostStatepriority::State_Attack4)
		return;


	//움직 일 때
	else if (Input == KeyType::Right ||
			Input == KeyType::Left ||
			Input == KeyType::KeepRight ||
			Input == KeyType::KeepLeft)
	{
		if (state == EMedGhostStatepriority::State_Idle)
		{

			if (forwordDirection != GetController()->GetInputDownX() &&
				forwordDirection != GetController()->GetInputPressedX())
			{
				SetSingleCallbackState(ConvertMedGhostStateToString(EMedGhostStatepriority::State_IdleToUturn), false);
				state = EMedGhostStatepriority::State_IdleToUturn;
				animator.SetAnimSpeed(10);

				isTurning = true;

				return;
			}
		}

	}

	else if (Input == KeyType::AttackKey1 ||
			Input == KeyType::AttackKey2 ||
			Input == KeyType::AttackKey3 ||
			Input == KeyType::AttackKey4)
	{
		if (state != EMedGhostStatepriority::State_Idle)
			return;

		animator.ResetAnimTimer();
		isCanMove = false;
		isCanJump = false;

		switch (Input)
		{
		case KeyType::AttackKey1:
			SetSingleCallbackState(ConvertMedGhostStateToString(EMedGhostStatepriority::State_Attack1), false, 7);
			state = EMedGhostStatepriority::State_Attack1;
			animator.SetAnimSpeed(15 * actionSpeed);
			break;
		case KeyType::AttackKey2:
			SetSingleCallbackState(ConvertMedGhostStateToString(EMedGhostStatepriority::State_Attack2), false, 7);
			state = EMedGhostStatepriority::State_Attack2;
			animator.SetAnimSpeed(15 * actionSpeed);
			break;
		case KeyType::AttackKey3:
			SetSingleCallbackState(ConvertMedGhostStateToString(EMedGhostStatepriority::State_Attack3), false, 6);
			state = EMedGhostStatepriority::State_Attack3;
			animator.SetAnimSpeed(15 * actionSpeed);
			break;
		case KeyType::AttackKey4:
			SetSingleCallbackState(ConvertMedGhostStateToString(EMedGhostStatepriority::State_Attack4), false, 7);
			state = EMedGhostStatepriority::State_Attack4;
			animator.SetAnimSpeed(15 * actionSpeed);
			break;
		default:
			break;
		}

	}
}
