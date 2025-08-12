#include "pch.h"
#include "SmallGhost.h"
#include "HitBox.h"
#include "Controller.h"

void SmallGhost::Init()
{
	Super::Init();

	SetState("Idle");
	state = ESmallGhostStatepriority::State_Idle;
	animator.SetAnimSpeed(10);

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
		animator.ResetAnimTimer(15);
		SetState("Hitted1", false);

	}
}

void SmallGhost::UpdateState(KeyType Input)
{
	
}
