#include "pch.h"
#include "W7.h"
#include "AIBossController.h"
#include "HitBoxManager.h"
#include "HitBox.h"
#include "random"
#include "Game.h"
#include "DebugLenderer.h"
#include "TimeManager.h"

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
	DamagedAble = true;

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

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.5, HitBoxType::Fixed, 0.3, GetController()->isPlayerController, this);
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
		colliderCenterPos.y += 120;

		//Vector hitBoxSize = { 0,0 };


		animHitbox->SetAnimHitBox(colliderCenterPos, hitBoxSize, SpriteManager::GetInstance()->GetTextures("HitBoxFX", "Attack_W7_WaterWave")
			, GetStat().atk * 1.7, HitBoxType::Movable, GetController()->isPlayerController, this);

		animHitbox->animator.SetAnimSpeed(10);
		animHitbox->SetMovingSpeed(Vector(600 * forwordDirection, 0));

		hitBoxManager->AddAnimHitBox(animHitbox, ImageAnchor::Bottomcenter);

		Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(animHitbox);

		break;
	}

	case W7::State_Attack4:
	{
		//1800 / 물기둥 너비 개수 만큼
		int numWaterWall = 5;
		std::vector<float> WaterWallSpawnList = { 100, 300, 500, 700, 900, 1100, 1300, 1500, 1700 };

		WaterWallSpawnList = ShuffleVector(WaterWallSpawnList);

		for (int i = 0; i < numWaterWall; i++)
		{
			AnimHitBox* animHitbox = hitBoxManager->CallAnimHitBox();
			Vector spawnPos = { WaterWallSpawnList[i], 500 };

			animHitbox->SetAnimHitBox(spawnPos, hitBoxSize, SpriteManager::GetInstance()->GetTextures("HitBoxFX", "WaterWAll")
				, GetStat().atk * 0.7, HitBoxType::Fixed, GetController()->isPlayerController, this);

			animHitbox->animator.SetAnimSpeed(12);


			TimeManager::GetInstance()->AddTimer(Timer([this, hitBoxManager, animHitbox]()
				{
					animHitbox->DisableCollition();
					hitBoxManager->AddAnimHitBox(animHitbox, ImageAnchor::Center);

					TimeManager::GetInstance()->AddTimer(Timer([this, animHitbox]() {animHitbox->SetCollition(); }, 1));
				}
			, 0.5 * i));
		}

		break;
	}

	case W7::State_Attack5:
	{
		hitbox = hitBoxManager->CallHitBox();

		colliderCenterPos.x += 150 * forwordDirection;
		colliderCenterPos.y += 30;
		hitBoxSize.x = 200;
		hitBoxSize.y = 80;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 1.0, GetController()->isPlayerController, this);
		break;
	}
	case W7::State_Attack6:
	{
		Vector currentPos;
		Vector jumPos;
		switch (animator.AnimTextureIndex)
		{
		case 6:
			jumPos = GetPos();
			jumPos.y -= 100;
			SetPos(jumPos);
			break;
		case 7:
			jumPos = GetPos();
			jumPos.y -= 100;
			SetPos(jumPos);
			animator.SetAnimSpeed(15);
			break;

		case 8:
		{
			if (moveCounter > 1)
				return;

			moveCounter = 1;

			if (GetController()->isPlayerController == true)
			{
				auto Emeny = Game::GetGameScene()->GetStage()->GetEnemy();
				if (Emeny == nullptr)
					flyingTargetPos = GetPos();

				else
					flyingTargetPos = Emeny->GetPos();
				
			}

			else
			{
				flyingTargetPos = static_cast<AIBossController*>(GetController())->GetTarget()->GetPos();
			}

			flyingStartPos = GetPos();

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}

		case 9:
		{
			if (moveCounter > 2)
				return;

			moveCounter = 2;

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}

		case 10:
		{
			if (moveCounter > 3)
				return;

			moveCounter = 3;

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}
		case 11:
		{
			if (moveCounter > 4)
				return;

			moveCounter = 4;

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}
		case 12:
		{
			if (moveCounter > 5)
				return;

			moveCounter = 5;

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}
		case 13:
		{
			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			break;
		}
		case 14:
		{
			if (moveCounter > 6)
				return;

			moveCounter = 6;

			currentPos = flyingStartPos + (flyingTargetPos - flyingStartPos) * (moveCounter / 6);
			SetPos(currentPos);
			moveCounter = 0;

			hitbox = hitBoxManager->CallHitBox();

			hitBoxSize.x = 80;
			hitBoxSize.y = 100;

			hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.5, GetController()->isPlayerController, this);

			break;
		}
		default:
			break;
		}
	}


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

		if (state != EW7PriorityState::State_Idle &&
			state != EW7PriorityState::State_Running)
			return;

		LookInputDir();

		if (state == EW7PriorityState::State_Running)
			return;

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

		LivingObject* target = nullptr;

		{
			if (GetController()->isPlayerController == false)
			{
				AIBossController* bossConroller = static_cast<AIBossController*>(GetController());
				target = bossConroller->GetTarget();
				bossConroller->LookTarget();
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
			Vector spawnedPos = Vector(targetPos.x + (targetLookDir * -50), targetPos.y);

			SetPos(spawnedPos);
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
		SetSingleCallbackState(ConvertW7StateToString(EW7PriorityState::State_Attack5), false, 22);
		state = EW7PriorityState::State_Attack5;

		break;
	}

	case KeyType::AttackKey6:
	{
		isCanMove = false;
		DamagedAble = false;

		LookEnemy();

		animator.ResetAnimTimer(10);
		SetMultiCallBackState(ConvertW7StateToString(EW7PriorityState::State_Attack6), false, {6, 7, 8, 9, 10, 11, 12, 13, 14 });
		state = EW7PriorityState::State_Attack6;

		readyAtk4 = false;

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

std::vector<float>& W7::ShuffleVector(std::vector<float>& vec)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vec.begin(), vec.end(), g);
	return vec;
}

LivingObject* W7::LookEnemy()
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
