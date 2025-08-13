#include "pch.h"
#include "SmallGhost.h"
#include "HitBox.h"
#include "Controller.h"
#include "AnimHitBox.h"
#include "HitBoxManager.h"

void SmallGhost::Init()
{
	Super::Init();

	SetState("Appear", false);
	state = ESmallGhostStatepriority::State_Appear;
	animator.SetAnimSpeed(10);

	SETTRIPLE(false)

	//ü �� �� ������Ÿ��, ���ݻ�Ÿ�, �̵��ӵ�, �����Ŀ�
	SetStat(ObjectStat(50, 10, 10, 0, 30, 10, 500));
}

void SmallGhost::Update(float deltaTime)
{
	Super::Update(deltaTime);

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

	SetState("Idle", true);
	state = ESmallGhostStatepriority::State_Idle;
	animator.SetAnimSpeed(10);
}

void SmallGhost::OnHitBoxSpawn()
{
	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	HitBox* hitbox = hitBoxManager->CallHitBox();

	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };

	if (state = ESmallGhostStatepriority::State_Attack)
	{

	}
}

void SmallGhost::OnHitted(HitBox* hitbox)
{
	Super::OnHitted(hitbox);
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
	//�̵���ư ����
	if (Input == KeyType::RELEASE)
	{
		if (state == ESmallGhostStatepriority::State_Running)
		{
			SetState(ConvertSmallGhostStateToString(ESmallGhostStatepriority::State_Idle), true);
			state = ESmallGhostStatepriority::State_Idle;
			animator.SetAnimSpeed(10);
		}
	}

	//���� �� ��
	else if (Input == KeyType::StartMove)
	{
		//�޸��� ���߿� �ݴ� �Է��� ���� ��
		if (state == ESmallGhostStatepriority::State_Running)
		{
			int inputDirect = (acceleration.x > 0) ? 1 : ((acceleration.x < 0) ? -1 : 0);
		}

	}
}
