#include "pch.h"
#include "W7.h"
#include "AIBossController.h"

void W7::Init()
{
	Super::Init();

	SetState("Appear", false);
	state = EW7PriorityState::State_Appear;
	animator.SetAnimSpeed(8);

	SETTRIPLE(false)

	//체 최대체력 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워 
	SetStat(ObjectStat(100, 100, 10, 5, 0, 0, 15, 0));

	if (GetController()->isPlayerController == false)
	{
		static_cast<AIBossController*>(GetController())->InitBossController(6, {3, 4, 5, 7, 3, 5});
	}
}

void W7::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == EW7PriorityState::State_Appear)
		return;

	UpdateState(Super::GetController()->GetInput());
}

void W7::Destroy()
{
}

void W7::OnAnimEnd()
{
	if (!IsActive)
	{
		Die();
	}

	if (state == EW7PriorityState::State_Appear)
	{
		SETTRIPLE(true)
	}

	SetState("Idle", true);
	state = EW7PriorityState::State_Idle;
	animator.SetAnimSpeed(30);
}

void W7::OnHitBoxSpawn()
{
}

void W7::Hitted(HitBox* hitbox)
{
	if (!DamagedAble)
		return;

	Super::Hitted(hitbox);
}

void W7::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{
		if (state != EW7PriorityState::State_Idle &&
			state != EW7PriorityState::State_Running)
			return;

		animator.ResetAnimTimer(15);
		SetState("Hitted2", false);
		state = EW7PriorityState::State_Hitted;
	}
}

void W7::UpdateState(KeyType Input)
{
	if (state != EW7PriorityState::State_Idle &&
		state != EW7PriorityState::State_Running)
		return;


	switch (Input)
	{
	case KeyType::KeepLeft:
		break;
	case KeyType::KeepRight:
		break;
	case KeyType::Left:
		break;
	case KeyType::Right:
		break;
	case KeyType::AttackKey1:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack1), false, 26);

		break;
	}
	case KeyType::AttackKey2:
	{
		animator.ResetAnimTimer(30);
		//SetState(ConvertW7StateToString(EW7PriorityState::State_Attack2), false, 26);
		SetMultiHitBoxState(ConvertW7StateToString(EW7PriorityState::State_Attack2), false, {16, 37});

		break;
	}

	case KeyType::AttackKey3:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack3), false, 26);

		break;
	}

	case KeyType::AttackKey4:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack4), false, 26);

		break;
	}

	case KeyType::AttackKey5:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack5), false, 26);

		break;
	}

	case KeyType::AttackKey6:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack6), false, 26);

		break;
	}

	default:
		break;
	}
}
