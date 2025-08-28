#include "pch.h"
#include "Nurse.h"
#include "HitBoxManager.h"
#include "SpriteManager.h"
#include "HitBox.h"
#include "Controller.h"
#include "AIController.h"
#include "Game.h"
#include "DebugLenderer.h"

void Nurse::Init()
{
	Super::Init();

	SetSingleCallbackState("Appear", false);
	state = ENurseStatepriority::State_Appear;
	animator.SetAnimSpeed(7);

	SETTRIPLE(false)

		//체 최대체력 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워 
		SetStat(ObjectStat(120, 120, 18, 5, 0, 100, 7, 0));

	//Multi 공격 패턴 설정
	{
		AttackProfile = {
			{1, 500.0, 1000, 1,0}, //공격 번호, 최소 거리, 최대거리, 가중치, 쿨타임
			{2, 0.0, 200, 1,0}  //atk 2 정보
		};
	}


	SetDetectRnage(1200);
	GetController()->SetAttackNum(2);
}

void Nurse::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == ENurseStatepriority::State_Appear)
		return;

	UpdateState(Super::GetController()->GetInput());
}

void Nurse::Destroy()
{
	Super::Destroy();
}

void Nurse::OnAnimEnd()
{
	if (!IsActive)
	{
		Die();
	}

	switch (state)
	{
	case Nurse::State_Appear:
		SETTRIPLE(true)
		break;

	case Nurse::State_Hitted1:
		break;

	case Nurse::State_Hitted2:
		break;

	case Nurse::State_Run:
		break;

	case Nurse::State_Teleport_Disappear:

		TeleportToTarget();

		animator.ResetAnimTimer(12);
		SetMultiCallBackState(ConvertPillStateToString(ENurseStatepriority::State_Attack1), false, {7, 12});
		state = ENurseStatepriority::State_Attack1;
		return;

	case Nurse::State_Teleport_Appear:
		break;

	case Nurse::State_Attack1: case Nurse::State_Attack2 :
		isCanMove = true;
		isCanJump = true;
		break;

	case Nurse::State_Idle:
		break;

	case Nurse::State_IdleToUturn:
		isTurning = false;
		forwordDirection *= -1;
		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
		break;

	case Nurse::State_max:
		break;

	default:
		break;
	}

	SetSingleCallbackState("Idle", true);
	state = ENurseStatepriority::State_Idle;
	animator.SetAnimSpeed(10);
	DamagedAble = true;
}

void Nurse::AnimCallBack()
{
	if (state != ENurseStatepriority::State_Attack1 &&
		state != ENurseStatepriority::State_Attack2 &&
		state != ENurseStatepriority::State_Teleport_Disappear)

		return;


	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	HitBox* hitbox = hitBoxManager->CallHitBox();
	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };

	switch (state)
	{
	case Nurse::State_Teleport_Disappear:
		break;

	case Nurse::State_Teleport_Appear:
		break;

	case Nurse::State_Attack1:

		if (animator.AnimTextureIndex == 7)
		{
			LookEnemy();
		}

		else if (animator.AnimTextureIndex == 12)
		{
			colliderCenterPos.x += 200 * forwordDirection;
			colliderCenterPos.y += 40;
			hitBoxSize.x = 150;
			hitBoxSize.y = 70;

			DamagedAble = true;

			hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 2.0, HitBoxType::Fixed, 0.3, GetController()->isPlayerController, this);
		}
		
		break;

	case Nurse::State_Attack2:
	{
		if (animator.AnimTextureIndex == 3)
		{
			colliderCenterPos.x += 50 * forwordDirection;
			colliderCenterPos.y -= 10;
			hitBoxSize.x = 150;
			hitBoxSize.y = 80;
		}

		else if (animator.AnimTextureIndex == 11)
		{
			colliderCenterPos.x += 50 * forwordDirection;
			colliderCenterPos.y -= 50;
			hitBoxSize.x = 150;
			hitBoxSize.y = 120;
		}

		else if (animator.AnimTextureIndex == 18)
		{
			colliderCenterPos.x += 50 * forwordDirection;
			colliderCenterPos.y += 10;
			hitBoxSize.x = 150;
			hitBoxSize.y = 80;
		}

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.0, HitBoxType::Fixed, 0.1, GetController()->isPlayerController, this);
		break;
	}
		

		break;

	case Nurse::State_max:
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

void Nurse::Hitted(HitBox* hitbox)
{
	if (!DamagedAble || !IsActive)
		return;

	Super::Hitted(hitbox);
}

void Nurse::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{

		if (state == ENurseStatepriority::State_Hitted1 ||
			state == ENurseStatepriority::State_Hitted2)
		{
			animator.ResetAnimTimer(20);
			SetSingleCallbackState("Hitted2", false);
			state = ENurseStatepriority::State_Hitted2;
		}

		else
		{
			animator.ResetAnimTimer(20);
			SetSingleCallbackState("Hitted1", false);
			state = ENurseStatepriority::State_Hitted1;
		}
	}
}

void Nurse::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;


	if (state == ENurseStatepriority::State_Hitted1 ||
		state == ENurseStatepriority::State_Hitted2 ||
		state == ENurseStatepriority::State_IdleToUturn ||
		state == ENurseStatepriority::State_Attack1 ||
		state == ENurseStatepriority::State_Attack2 ||
		state == ENurseStatepriority::State_Teleport_Disappear)
		return;

	else if (Input == KeyType::Right ||
		Input == KeyType::Left ||
		Input == KeyType::KeepRight ||
		Input == KeyType::KeepLeft)
	{
		if (state == ENurseStatepriority::State_Idle)
		{

			if (forwordDirection != GetController()->GetInputDownX() &&
				forwordDirection != GetController()->GetInputPressedX())
			{
				SetSingleCallbackState(ConvertPillStateToString(ENurseStatepriority::State_IdleToUturn), false);
				state = ENurseStatepriority::State_IdleToUturn;
				animator.SetAnimSpeed(20);

				isTurning = true;

				return;
			}
		}

	}

	else if (Input == KeyType::AttackKey1 ||
		Input == KeyType::AttackKey2)
	{
		if (state != ENurseStatepriority::State_Idle)
			return;

		animator.ResetAnimTimer();
		isCanMove = false;
		isCanJump = false;

		switch (Input)
		{
		case KeyType::AttackKey1:
			SetSingleCallbackState(ConvertPillStateToString(ENurseStatepriority::State_Teleport_Disappear), false);
			state = ENurseStatepriority::State_Teleport_Disappear;
			animator.SetAnimSpeed(18 * actionSpeed);
			DamagedAble = false;
			break;
		case KeyType::AttackKey2:
			SetMultiCallBackState(ConvertPillStateToString(ENurseStatepriority::State_Attack2), false, {3, 11, 18});
			state = ENurseStatepriority::State_Attack2;
			animator.SetAnimSpeed(20 * actionSpeed);
			break;
		default:
			break;
		}

	}
}

void Nurse::TeleportToTarget()
{
	LivingObject* target = nullptr;

	{
		if (GetController()->isPlayerController == false)
		{
			AIController* aiController = static_cast<AIController*>(GetController());
			target = aiController->GetTarget();
		}

		else
		{
			target = LookEnemy();

		}
	}


	if (target)
	{
		Vector targetPos = target->GetPos();
		int targetLookDir = target->forwordDirection;
		Vector spawnedPos = Vector(targetPos.x + (targetLookDir * -100), targetPos.y);

		SetPos(spawnedPos);
	}
}

LivingObject* Nurse::LookEnemy()
{
	auto Emeny = Game::GetGameScene()->GetStage()->GetEnemy();

	if (Emeny == nullptr)
		return this;


	int moveDir = (GetPos().x - Emeny->GetPos().x >= 0) ? -1 : 1;

	if (moveDir != 0)
		forwordDirection = moveDir;

	renderingFlipOrder = (moveDir == -1) ? true : (moveDir == 1) ? false : renderingFlipOrder;

	return Emeny;
}
