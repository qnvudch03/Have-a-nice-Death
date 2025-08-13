#include "pch.h"
#include "SmallGhost.h"
#include "HitBox.h"
#include "Controller.h"

void SmallGhost::Init()
{
	Super::Init();

	SetState("Appear", false);
	state = ESmallGhostStatepriority::State_Appear;
	animator.SetAnimSpeed(10);

	SETTRIPLE(false)

	//체 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워
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
	
}
