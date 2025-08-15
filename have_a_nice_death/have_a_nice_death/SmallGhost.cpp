#include "pch.h"
#include "SmallGhost.h"
#include "HitBox.h"
#include "Controller.h"
#include "AnimHitBox.h"
#include "HitBoxManager.h"
#include "SpriteManager.h"

void SmallGhost::Init()
{
	Super::Init();

	SetState("Appear", false);
	state = ESmallGhostStatepriority::State_Appear;
	animator.SetAnimSpeed(10);

	SETTRIPLE(false)

		//체 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워
		SetStat(ObjectStat(50, 50, 10, 10, 0, 30, 10, 500));
}

void SmallGhost::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == ESmallGhostStatepriority::State_Appear)
		return;

	UpdateState(Super::GetController()->GetInput());

}

void SmallGhost::Destroy()
{
	Super::Destroy();
}

void SmallGhost::OnAnimEnd()
{
	if (!IsActive)
	{
		Die();
	}

	if (state == ESmallGhostStatepriority::State_Appear)
	{
		SETTRIPLE(true)
	}

	else if (state == ESmallGhostStatepriority::State_IdleToUturn)
	{
		isTurning = false;
		forwordDirection *= -1;
		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
	}

	else if (state == ESmallGhostStatepriority::State_Attack)
	{
		isCanMove = true;
		isCanJump = true;
	}

	SetState("Idle", true);
	state = ESmallGhostStatepriority::State_Idle;
	animator.SetAnimSpeed(10);
}

void SmallGhost::OnHitBoxSpawn()
{
	if (state != ESmallGhostStatepriority::State_Attack)
		return;

	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	AnimHitBox* animHitbox = hitBoxManager->CallAnimHitBox();

	if (animHitbox == nullptr)
		return;


	{
		Vector colliderCenterPos = collider->GetCenterPos();
		Vector animHitBoxSpawnPos = colliderCenterPos;
		animHitBoxSpawnPos.x += forwordDirection * 170;
		animHitBoxSpawnPos.y += 50;

		Vector hitBoxSize = { 0,0 };


		animHitbox->SetAnimHitBox(animHitBoxSpawnPos, hitBoxSize, SpriteManager::GetInstance()->GetTextures("HitBoxFX", "Attack_SmallGhost")
			, GetStat().atk, HitBoxType::Fixed, GetController()->isPlayerController, this);

		animHitbox->animator.SetAnimSpeed(30);
	}
	


	hitBoxManager->AddAnimHitBox(animHitbox);
}

void SmallGhost::Hitted(HitBox* hitbox)
{
	if (!DamagedAble)
		return;

	Super::Hitted(hitbox);
}

void SmallGhost::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{

		if (state == ESmallGhostStatepriority::State_Hitted1 ||
			state == ESmallGhostStatepriority::State_Hitted2)
		{
			animator.ResetAnimTimer(15);
			SetState("Hitted2", false);
			state = ESmallGhostStatepriority::State_Hitted2;
		}

		else
		{
			animator.ResetAnimTimer(15);
			SetState("Hitted1", false);
			state = ESmallGhostStatepriority::State_Hitted1;
		}


	}
}

void SmallGhost::UpdateState(KeyType Input)
{
	if (state == ESmallGhostStatepriority::State_Hitted1 ||
		state == ESmallGhostStatepriority::State_Hitted2 ||
		state == ESmallGhostStatepriority::State_IdleToUturn ||
		state == ESmallGhostStatepriority::State_Attack)
		return;


	//이동버튼 해제
	if (Input == KeyType::RELEASE)
	{
		if (state == ESmallGhostStatepriority::State_Running)
		{
			SetState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Idle), true);
			state = ESmallGhostStatepriority::State_Idle;
			animator.SetAnimSpeed(10);
		}
	}

	//움직 일 때
	else if (Input == KeyType::Right ||
		Input == KeyType::Left ||
		Input == KeyType::KeepRight ||
		Input == KeyType::KeepLeft)
	{
		if (state == ESmallGhostStatepriority::State_Idle ||
			state == ESmallGhostStatepriority::State_Running)
		{

			if (forwordDirection != GetController()->GetInputDownX() &&
				forwordDirection != GetController()->GetInputPressedX())
			{
				SetState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_IdleToUturn), false);
				state = ESmallGhostStatepriority::State_IdleToUturn;
				animator.SetAnimSpeed(10);

				isTurning = true;

				return;
			}

			if (state != ESmallGhostStatepriority::State_Running)
			{
				SetState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Running), true);
				state = ESmallGhostStatepriority::State_Running;
				animator.SetAnimSpeed(10);
			}


		}

	}

	else if (Input == KeyType::Z)
	{
		if (state != ESmallGhostStatepriority::State_Idle)
			return;

		animator.ResetAnimTimer();
		SetState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Attack), false, 17);
		state = ESmallGhostStatepriority::State_Attack;
		animator.SetAnimSpeed(15);

		isCanMove = false;
		isCanJump = false;

		AddAcceleration(Vector(0,50));
	}
}
