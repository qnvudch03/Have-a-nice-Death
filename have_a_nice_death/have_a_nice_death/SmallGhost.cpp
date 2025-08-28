#include "pch.h"
#include "SmallGhost.h"
#include "HitBox.h"
#include "Controller.h"
#include "AnimHitBox.h"
#include "HitBoxManager.h"
#include "TimeManager.h"
#include "SpriteManager.h"

void SmallGhost::Init()
{
	Super::Init();

	SetSingleCallbackState("Appear", false);
	state = ESmallGhostStatepriority::State_Appear;
	animator.SetAnimSpeed(10);

	SETTRIPLE(false)

	//ü �ִ�ü�� �� �� ������Ÿ��, ���ݻ�Ÿ�, �̵��ӵ�, �����Ŀ� 
	SetStat(ObjectStat(50, 50, 10, 5, 0, 200, 10, 900));

	AttackProfile = {
			{1, 50.0, 250, 1,0} //���� ��ȣ, �ּ� �Ÿ�, �ִ�Ÿ�, ����ġ, ��Ÿ��
	};

	SetDetectRnage(700);
	GetController()->SetAttackNum(1);

	resistStunMax = 3;
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

	SetSingleCallbackState("Idle", true);
	state = ESmallGhostStatepriority::State_Idle;
	animator.SetAnimSpeed(10);
}

void SmallGhost::AnimCallBack()
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
	


	hitBoxManager->AddAnimHitBox(animHitbox, ImageAnchor::Center);
}

void SmallGhost::Hitted(HitBox* hitbox)
{
	if (!DamagedAble || !IsActive)
		return;

	Super::Hitted(hitbox);
}

void SmallGhost::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{

		if (stunCounter < resistStunMax)
		{
			if (state == ESmallGhostStatepriority::State_Hitted1 ||
				state == ESmallGhostStatepriority::State_Hitted2)
			{
				animator.ResetAnimTimer(20);
				SetSingleCallbackState("Hitted2", false);
				state = ESmallGhostStatepriority::State_Hitted2;
			}

			else
			{
				animator.ResetAnimTimer(20);
				SetSingleCallbackState("Hitted1", false);
				state = ESmallGhostStatepriority::State_Hitted1;
			}

			stunCounter++;

			TimeManager::GetInstance()->AddTimer(Timer([this]() {stunCounter = 0; }, 3));
		}

		
	}

	else
	{
		state = ESmallGhostStatepriority::State_Death;
	}
}

void SmallGhost::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;


	if (state == ESmallGhostStatepriority::State_Hitted1 ||
		state == ESmallGhostStatepriority::State_Hitted2 ||
		state == ESmallGhostStatepriority::State_IdleToUturn ||
		state == ESmallGhostStatepriority::State_Attack)
		return;


	//�̵���ư ����
	if (Input == KeyType::RELEASE)
	{
		if (state == ESmallGhostStatepriority::State_Running)
		{
			SetSingleCallbackState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Idle), true);
			state = ESmallGhostStatepriority::State_Idle;
			animator.SetAnimSpeed(10);
		}
	}

	//���� �� ��
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
				SetSingleCallbackState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_IdleToUturn), false);
				state = ESmallGhostStatepriority::State_IdleToUturn;
				animator.SetAnimSpeed(10);

				isTurning = true;

				return;
			}

			if (state != ESmallGhostStatepriority::State_Running)
			{
				SetSingleCallbackState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Running), true);
				state = ESmallGhostStatepriority::State_Running;
				animator.SetAnimSpeed(10);
			}


		}

	}

	else if (Input == KeyType::AttackKey1)
	{
		if (state != ESmallGhostStatepriority::State_Idle &&
			state != ESmallGhostStatepriority::State_Running)
			return;

		animator.ResetAnimTimer();
		SetSingleCallbackState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Attack), false, 17);
		state = ESmallGhostStatepriority::State_Attack;
		animator.SetAnimSpeed(15 * actionSpeed);

		isCanMove = false;
		isCanJump = false;

		AddAcceleration(Vector(0,50));
	}
}
