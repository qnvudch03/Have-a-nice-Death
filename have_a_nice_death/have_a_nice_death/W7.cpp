#include "pch.h"
#include "W7.h"
#include "AIBossController.h"
#include "random"

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

	switch (state)
	{
	case W7::State_Appear:
		SETTRIPLE(true)
		break;
	case W7::State_Death:
		break;
	case W7::State_Hitted:
		break;
	case W7::State_Attack1:
		break;
	case W7::State_Attack2:
		break;
	case W7::State_Attack3:
		break;
	case W7::State_Attack4:
		break;
	case W7::State_Attack5:
		break;
	case W7::State_Attack6:
		break;
	case W7::State_TeleportAppear:
	{
		animator.ResetAnimTimer(25);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack4), false, 13);
		state = EW7PriorityState::State_Attack4;

		DamagedAble = true;

		return;
	}
	case W7::State_TeleportDisapera:
	{
		TeleportMapBound();

		animator.ResetAnimTimer(15);
		SetState(ConvertW7StateToString(EW7PriorityState::State_TeleportAppear), false);
		state = EW7PriorityState::State_TeleportAppear;

		return;
	}
		break;
	default:
		break;
	}


	SetState("Idle", true);
	state = EW7PriorityState::State_Idle;
	animator.SetAnimSpeed(30);

	if (GetController()->isPlayerController == false)
	{
		static_cast<AIBossController*>(GetController())->StartAttackInterval();
	}
}

void W7::OnHitBoxSpawn()
{
}

void W7::Hitted(HitBox* hitbox)
{
	if (!DamagedAble || !IsActive)
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
		SetState("Hitted", false);
		state = EW7PriorityState::State_Hitted;
	}
}

void W7::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;

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
		state = EW7PriorityState::State_Attack1;

		break;
	}
	case KeyType::AttackKey2:
	{
		animator.ResetAnimTimer(30);
		//SetState(ConvertW7StateToString(EW7PriorityState::State_Attack2), false, 26);
		SetMultiHitBoxState(ConvertW7StateToString(EW7PriorityState::State_Attack2), false, {16, 37});
		state = EW7PriorityState::State_Attack2;

		break;
	}

	case KeyType::AttackKey3:
	{
		animator.ResetAnimTimer(15);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack3), false, 10);
		state = EW7PriorityState::State_Attack3;

		break;
	}

	case KeyType::AttackKey4:
	{
		/*animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack4), false, 14);
		state = EW7PriorityState::State_Attack4;*/

		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_TeleportDisapera), false);
		state = EW7PriorityState::State_TeleportDisapera;

		DamagedAble = false;

		break;
	}

	case KeyType::AttackKey5:
	{
		animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack5), false, 21);
		state = EW7PriorityState::State_Attack5;

		break;
	}

	case KeyType::AttackKey6:
	{
		animator.ResetAnimTimer(30);
		SetMultiHitBoxState(ConvertW7StateToString(EW7PriorityState::State_Attack6), false, {8, 9, 10, 11, 12, 13, 14});
		state = EW7PriorityState::State_Attack6;

		break;
	}
	default:
		break;
	}
}

void W7::TeleportMapBound()
{
	std::random_device rd;

	int lookDir = (rd() % 2);

	if (lookDir == 1)
	{
		forwordDirection = lookDir;
		SetPos(Vector(100, 678));

	}

	else
	{
		lookDir = -1;
		forwordDirection = -1;
		SetPos(Vector(GWinSizeX - 100, 678));
	}

	renderingFlipOrder = (lookDir == -1) ? true : (lookDir == 1) ? false : renderingFlipOrder;
}
