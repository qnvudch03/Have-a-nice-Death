#include "pch.h"
#include "W7.h"
#include "AIBossController.h"
#include "HitBoxManager.h"
#include "HitBox.h"
#include "random"
#include "Game.h"
#include "DebugLenderer.h"

void W7::Init()
{
	Super::Init();

	SetSingleCallbackState("Appear", false);
	state = EW7PriorityState::State_Appear;
	animator.SetAnimSpeed(8);

	SETTRIPLE(false)

		//체 최대체력 공 방 공격쿨타임, 공격사거리, 이동속도, 점프파워 
		SetStat(ObjectStat(100, 100, 10, 5, 0, 0, 5, 0));

	if (GetController()->isPlayerController == false)
	{
		static_cast<AIBossController*>(GetController())->InitBossController(6, { 3, 4, 5, 7, 3, 5 });
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
	{
		animator.ResetAnimTimer(25);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_TeleportAppear), false);
		state = EW7PriorityState::State_TeleportAppear;

		return;
	}
	case W7::State_TeleportAppear:
	{

		if (readyAtk4)
		{
			animator.ResetAnimTimer(25);
			SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Attack4), false, 13);
			state = EW7PriorityState::State_Attack4;

			DamagedAble = true;

			return;
		}

		break;

	}
	case W7::State_TeleportDisapera:
	{
		TeleportMapBound();

		animator.ResetAnimTimer(25);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_TeleportAppear), false);
		state = EW7PriorityState::State_TeleportAppear;

		return;
	}
	break;
	default:
		break;
	}


	SetSingleCallbackState("Idle", true);
	state = EW7PriorityState::State_Idle;
	animator.SetAnimSpeed(30);
	isCanMove = true;

	if (GetController()->isPlayerController == false)
	{
		static_cast<AIBossController*>(GetController())->StartAttackInterval();
	}
}

void W7::AnimCallBack()
{
	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	HitBox* hitbox = nullptr;
	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };



	switch (state)
	{
	case W7::State_Attack1:
	{
		hitbox = hitBoxManager->CallHitBox();

		colliderCenterPos.x += 100 * forwordDirection;
		colliderCenterPos.y += 20;
		hitBoxSize.x = 130;
		hitBoxSize.y = 130;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.5, GetController()->isPlayerController, this);
		break;
	}
	case W7::State_Attack2:
	{
		hitbox = hitBoxManager->CallHitBox();

		colliderCenterPos.x += 100 * forwordDirection;
		//colliderCenterPos.y += 30;
		hitBoxSize.x = 200;
		hitBoxSize.y = 70;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.3, GetController()->isPlayerController, this);
		break;
	}

	case W7::State_Attack3:
	{
		AnimHitBox* animHitbox = hitBoxManager->CallAnimHitBox();

		if (animHitbox == nullptr)
			return;

		colliderCenterPos.x += forwordDirection * 170;
		colliderCenterPos.y += 50;

		Vector hitBoxSize = { 0,0 };


		animHitbox->SetAnimHitBox(colliderCenterPos, hitBoxSize, SpriteManager::GetInstance()->GetTextures("HitBoxFX", "Attack_W7_WaterWave")
			, GetStat().atk, HitBoxType::Movable, GetController()->isPlayerController, this);

		animHitbox->animator.SetAnimSpeed(10);
		animHitbox->SetMovingSpeed(Vector(100, 0));

		hitBoxManager->AddAnimHitBox(animHitbox);

		Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(animHitbox);

		break;
	}

	case W7::State_Attack4:
		break;
	case W7::State_Attack5:
		break;
	case W7::State_Attack6:
		break;
	default:
		break;
	}


	if (hitbox == nullptr)
		return;

	hitBoxManager->AddHitBox(hitbox);

	Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(hitbox);


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
		SetSingleCallbackState("Hitted", false);
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
	case KeyType::KeepRight:
	case KeyType::Left:
	case KeyType::Right:

		if (state != EW7PriorityState::State_Idle)
			return;

		LookInputDir();

		animator.ResetAnimTimer(30);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Running), true);
		state = EW7PriorityState::State_Running;
		break;

	case KeyType::AttackKey1:
	{
		isCanMove = false;

		animator.ResetAnimTimer(30);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Attack1), false, 26);
		state = EW7PriorityState::State_Attack1;

		break;
	}
	case KeyType::AttackKey2:
	{
		isCanMove = false;

		animator.ResetAnimTimer(30);

		if (GetController()->isPlayerController == false)
		{
			AIBossController* bossConroller = static_cast<AIBossController*>(GetController());
			LivingObject* target = bossConroller->GetTarget();

			if (target)
			{
				Vector targetPos = target->GetPos();
				int targetLookDir = target->forwordDirection;
				Vector spawnedPos = Vector(targetPos.x + (targetLookDir * -50), targetPos.y);

				SetPos(spawnedPos);
				bossConroller->LookTarget();
			}
		}

		SetMultiCallBackState(ConvertW7StateToString(EW7PriorityState::State_Attack2), false, { 17, 38 });
		state = EW7PriorityState::State_Attack2;

		break;
	}

	case KeyType::AttackKey3:
	{
		isCanMove = false;

		animator.ResetAnimTimer(15);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Attack3), false, 10);
		state = EW7PriorityState::State_Attack3;

		break;
	}

	case KeyType::AttackKey4:
	{
		/*animator.ResetAnimTimer(30);
		SetState(ConvertW7StateToString(EW7PriorityState::State_Attack4), false, 14);
		state = EW7PriorityState::State_Attack4;*/
		isCanMove = false;

		animator.ResetAnimTimer(30);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_TeleportDisapera), false);
		state = EW7PriorityState::State_TeleportDisapera;

		DamagedAble = false;
		readyAtk4 = true;

		break;
	}

	case KeyType::AttackKey5:
	{
		isCanMove = false;

		animator.ResetAnimTimer(30);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Attack5), false, 21);
		state = EW7PriorityState::State_Attack5;

		break;
	}

	case KeyType::AttackKey6:
	{
		isCanMove = false;

		animator.ResetAnimTimer(20);
		SetMultiCallBackState(ConvertW7StateToString(EW7PriorityState::State_Attack6), false, { 8, 9, 10, 11, 12, 13, 14 });
		state = EW7PriorityState::State_Attack6;

		break;
	}

	case KeyType::MAX:

		if (state == EW7PriorityState::State_Idle)
			return;

		animator.ResetAnimTimer(30);
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Idle), true);
		state = EW7PriorityState::State_Idle;
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
		SetPos(Vector(150, 678));

	}

	else
	{
		lookDir = -1;
		forwordDirection = -1;
		SetPos(Vector(GWinSizeX - 150, 678));
	}

	renderingFlipOrder = (lookDir == -1) ? true : (lookDir == 1) ? false : renderingFlipOrder;
}
