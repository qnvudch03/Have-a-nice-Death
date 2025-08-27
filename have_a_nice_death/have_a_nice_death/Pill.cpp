#include "pch.h"
#include "Pill.h"
#include "HitBoxManager.h"
#include "SpriteManager.h"
#include "HitBox.h"
#include "AnimHitBox.h"
#include "Controller.h"
#include "Game.h"
#include "DebugLenderer.h"

void Pill::Init()
{
	Super::Init();

	SetSingleCallbackState("Appear", false);
	state = EPillStatepriority::State_Appear;
	animator.SetAnimSpeed(15);

	SETTRIPLE(false)

	//체 최대체력 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워 
	SetStat(ObjectStat(50, 50, 20, 7, 0, 100, 10, 700));

	SetDetectRnage(500);
	GetController()->SetAttackNum(2);
}

void Pill::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == EPillStatepriority::State_Appear)
		return;

	UpdateState(Super::GetController()->GetInput());
}

void Pill::Destroy()
{
	Super::Destroy();
}

void Pill::OnAnimEnd()
{
	if (!IsActive)
	{
		Die();
	}

	if (state == EPillStatepriority::State_Appear)
	{
		SETTRIPLE(true)
	}

	else if (state == EPillStatepriority::State_IdleToUturn)
	{
		isTurning = false;
		forwordDirection *= -1;
		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
	}

	else if (state == EPillStatepriority::State_Attack1_end ||
		state == EPillStatepriority::State_Attack2)
	{
		isCanMove = true;
		isCanJump = true;
	}

	if (state == EPillStatepriority::State_Attack1_start)
	{
		SetMultiCallBackState(ConvertPillStateToString(EPillStatepriority::State_Attack1), false, { 0, 14 });
		state = EPillStatepriority::State_Attack1;
		animator.SetAnimSpeed(20 * actionSpeed);
		return;
	}

	if (state == EPillStatepriority::State_Attack1)
	{
		SetSingleCallbackState(ConvertPillStateToString(EPillStatepriority::State_Attack1_end), false);
		state = EPillStatepriority::State_Attack1_end;
		animator.SetAnimSpeed(20 * actionSpeed);
		return;
	}

	SetSingleCallbackState("Idle", true);
	state = EPillStatepriority::State_Idle;
	animator.SetAnimSpeed(20);
}

void Pill::AnimCallBack()
{
	if (state != EPillStatepriority::State_Attack1 &&
		state != EPillStatepriority::State_Attack2)

		return;

	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();

	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };

	if (state == EPillStatepriority::State_Attack1)
	{
		colliderCenterPos.y -= 30;

		hitBoxSize.x = 130;
		hitBoxSize.y = 100;

		HitBox* hitbox = hitBoxManager->CallHitBox();

		if (hitbox == nullptr)
			return;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.5, HitBoxType::Fixed, 0.5, GetController()->isPlayerController, this);

		hitBoxManager->AddHitBox(hitbox);

		Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(hitbox);
	}

	else if (state == EPillStatepriority::State_Attack2)
	{
		colliderCenterPos.x += forwordDirection * 200;
		colliderCenterPos.y -= 50;

		AnimHitBox* animHitBox = hitBoxManager->CallAnimHitBox();

		if (animHitBox == nullptr)
			return;

		animHitBox->SetAnimHitBox(colliderCenterPos, hitBoxSize, SpriteManager::GetInstance()->GetTextures("HitBoxFX", "Attack_Pill_Smoke")
			, GetStat().atk * 2.0, HitBoxType::Fixed, GetController()->isPlayerController, this);

		animHitBox->animator.SetAnimSpeed(20);

		hitBoxManager->AddAnimHitBox(animHitBox, ImageAnchor::Center);

		Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(animHitBox);


	}
}

void Pill::Hitted(HitBox* hitbox)
{
	if (!DamagedAble || !IsActive)
		return;

	Super::Hitted(hitbox);
}

void Pill::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{
		animator.ResetAnimTimer(30);
		SetSingleCallbackState("Hitted", false);
		state = EPillStatepriority::State_Hitted;
	}
}

void Pill::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;


	if (state == EPillStatepriority::State_Hitted ||
		state == EPillStatepriority::State_IdleToUturn ||
		state == EPillStatepriority::State_Attack1 ||
		state == EPillStatepriority::State_Attack2 ||
		state == EPillStatepriority::State_Attack1_start ||
		state == EPillStatepriority::State_Attack1_end)
		return;


	//움직 일 때
	else if (Input == KeyType::Right ||
		Input == KeyType::Left ||
		Input == KeyType::KeepRight ||
		Input == KeyType::KeepLeft)
	{
		if (state == EPillStatepriority::State_Idle)
		{

			if (forwordDirection != GetController()->GetInputDownX() &&
				forwordDirection != GetController()->GetInputPressedX())
			{
				SetSingleCallbackState(ConvertPillStateToString(EPillStatepriority::State_IdleToUturn), false);
				state = EPillStatepriority::State_IdleToUturn;
				animator.SetAnimSpeed(20);

				isTurning = true;

				return;
			}
		}

	}

	else if (Input == KeyType::AttackKey1 ||
			Input == KeyType::AttackKey2)
	{
		if (state != EPillStatepriority::State_Idle)
			return;

		animator.ResetAnimTimer();
		isCanMove = false;
		isCanJump = false;

		switch (Input)
		{
		case KeyType::AttackKey1:
			SetSingleCallbackState(ConvertPillStateToString(EPillStatepriority::State_Attack1_start), false);
			state = EPillStatepriority::State_Attack1_start;
			animator.SetAnimSpeed(20 * actionSpeed);
			break;
		case KeyType::AttackKey2:
			SetSingleCallbackState(ConvertPillStateToString(EPillStatepriority::State_Attack2), false, 23);
			state = EPillStatepriority::State_Attack2;
			animator.SetAnimSpeed(20 * actionSpeed);
			break;
		default:
			break;
		}

	}
}
