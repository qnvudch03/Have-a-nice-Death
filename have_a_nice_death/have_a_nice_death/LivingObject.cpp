#include "pch.h"
#include "LivingObject.h"
#include "Controller.h"
#include "Collider.h"
#include "Game.h"
#include "DebugLenderer.h"
#include "Animaotr.h"
#include "HitBox.h"
#include "TimeManager.h"
#include "GameScene.h"

//void LivingObject::Init()
//{
//	Super::Init();
//}
//
//void LivingObject::Update(float deltaTime)
//{
//	Super::Update(deltaTime);
//}

void LivingObject::Init()
{
	Super::Init();
}

void LivingObject::Update(float deltaTime)
{
	if (_controller != nullptr)
		_controller->Update(deltaTime);

	auto game = Game::GetInstance();

	Super::Update(deltaTime);

	if (!IsActive)
		return;

	for (auto sensor : SensorArray)
	{
		Sensor* currentsencor = (*sensor);
		currentsencor->Update(animator.GetAnimTexture()->GetTextureSize());

		if (game->GetScene()->IsDbugMode)
		{
			game->GetDebugLenderer()->ReserveSensor(currentsencor);
		}
	}

	ApplyEnvironment(deltaTime);

}

void LivingObject::Destroy()
{
	Super::Destroy();
}

void LivingObject::SetDebugMode(bool debugmode)
{
	for (auto& Iter : *ownTextures)
	{
		for (auto& iter : Iter.second)
		{
			iter->SetDrawBound(debugmode);
		}
	}
}

void LivingObject::SetCollider()
{
	if (ownTextures->find("Idle") == ownTextures->end())
		return;

	//첫 ideal 모션의 크기를 가져와 collider로 설정한다.
	collider = new Collider(this, (*ownTextures)["Idle"][0]->GetTextureSize());
}

void LivingObject::SetSingleCallbackState(std::string state, bool IsLoop, int32 atkIndex)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	//기본 애니메이션 일 경우
	if (atkIndex == -1)
	{
		SetAnimaotrTextures(&(*ownTextures)[state], IsLoop);
	}

	//만약 공격 모션이라면
	else if(atkIndex >= 0)
	{
		SetAnimaotrTextures(&(*ownTextures)[state], IsLoop, true, atkIndex);
	}
}

void LivingObject::SetMultiCallBackState(std::string state, bool IsLoop, std::vector<int32> atkIndexs)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	//기본 애니메이션 일 경우
	if (atkIndexs.size() != 0)
	{
		SetManyAnimaotrTextures(&(*ownTextures)[state], IsLoop, true, atkIndexs);
	}

}

void LivingObject::Die()
{
	//스테이지에 자신의 사망을 알림(플레이어, Enemy 일떄의 처리가 다름)
	OnDie();

	Game::GetGameScene()->EraseFromGame(this);
}

void LivingObject::LookInputDir()
{
	KeyType currentInput = GetController()->GetInput();
	int32 movedir = 0;

	if (currentInput == KeyType::Right ||
		currentInput == KeyType::KeepRight)
	{
		movedir = 1;
	}

	else if (currentInput == KeyType::Left ||
		currentInput == KeyType::KeepLeft)
	{
		movedir = -1;
	}



	if (movedir != 0)
		forwordDirection = movedir;

	renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
}

void LivingObject::ApplyEnvironment(float deltaTime)
{
	Vector inPut = { 0,0 };
	acceleration = { 0,0 };
	velocity.x *= 0.98;

	KeyType currentInput = _controller->GetInput();
	KeyType pastInput = _controller->GetPastInput();

	if (abs(velocity.x) < 0.01)
	{
		velocity.x = 0;
	}

	if (abs(velocity.y) < 0.01)
	{
		velocity.y = 0;
	}

	if (currentInput == KeyType::RELEASE &&
		(pastInput == KeyType::KeepLeft || pastInput == KeyType::KeepRight))
	{
		velocity.x *= 0.3;
	}

	if (groundSensor->IsActive())
	{
		//속도가 아래 방향일 경우에만 적용
		if (velocity.y > 0)
		{
			velocity.y = 0;
			OnLanded();
		}
			
	}

	else
	{
		if(isEffectGravity)
			AddForce(Vector(0, 1), gravityPower);
	}

	if (isCanMove && !isTurning)
	{

		if (currentInput == KeyType::KeepLeft ||
			currentInput == KeyType::KeepRight)
		{
			inPut.x = forwordDirection;
		}

		/*	else if (currentInput == KeyType::Left)
			{
				inPut.x = -1;
			}*/
		if(!IsessentialAnim)
			AddForce(inPut, objectStat.moveForce);

		//공중상태에서는 가속도를 살짝 낮추자
		if (!groundSensor->IsActive())
			acceleration.x *= 0.8;
	}

	if (isCanJump)
	{
		
		if (currentInput == KeyType::SpaceBar &&
			pastInput != KeyType::SpaceBar)
		{
			if (groundSensor->IsActive() && velocity.y <= 0)
				AddForce(Vector(0, -1), objectStat.jumpPower);
		}
		
	}

	velocity += acceleration * deltaTime;

	if (wallSensor->IsActive())
	{
		velocity.x = 0;
	}

	Vector currentPos = GetPos();
	Vector movedPos = currentPos + velocity;

	SetPos(movedPos);

	collider->Update();
}

void LivingObject::AddStatByIndex(int index, float amount)
{
	switch (index)
	{
	case 1:	objectStat.hp += amount;
		if (objectStat.hp > objectStat.maxhp)
		{
			objectStat.hp = objectStat.maxhp;
		}

		if (objectStat.hp < 0)
		{
			objectStat.hp = 0;
		}

		return;

	case 2:	objectStat.maxhp += amount;				return;
	case 3:	objectStat.atk += amount;				return;
	case 4:	objectStat.def += amount;				return;
	case 5:	objectStat.attack_duration += amount;	return;
	case 6:	objectStat.attack_range += amount;		return;
	case 7:	objectStat.moveForce += amount;			return;
	case 8:	objectStat.jumpPower += amount;			return;
	default:										return;
	}
}

void LivingObject::SetStatByIndex(int index, float amount)
{
	switch (index)
	{
	case 1:	objectStat.hp = amount;					return;
	case 2:	objectStat.maxhp = amount;				return;
	case 3:	objectStat.atk = amount;				return;
	case 4:	objectStat.def = amount;				return;
	case 5:	objectStat.attack_duration = amount;	return;
	case 6:	objectStat.attack_range = amount;		return;
	case 7:	objectStat.moveForce = amount;			return;
	case 8:	objectStat.jumpPower = amount;			return;
	default:										return;
	}
}

void LivingObject::Hitted(HitBox* hitbox)
{
	DamagedAble = false;
	isCanMove = false;
	isCanJump = false;

	TimeManager::GetInstance()->AddTimer(Timer([this]()
		{
			DamagedAble = true;
			isCanMove = true;
			isCanJump = true;
			IsessentialAnim = false;
			isEffectGravity = true;
		},
		0.5));

	velocity.x = 0;

	if (forwordDirection == hitbox->GetForwordDirection())
	{
		forwordDirection *= -1;

		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
	}

	TakeDamage(hitbox->damage);

	if (OnHitted != nullptr)
	{
		OnHitted();
	}
}

void LivingObject::TakeDamage(float Damage)
{
	float damageAmount = (Damage - objectStat.def <= 0) ? 0 : Damage - objectStat.def;
	objectStat.hp -= damageAmount;

	if (objectStat.hp <= 0)
	{
		animator.ResetAnimTimer(20);
		SetSingleCallbackState("Death", false);
		IsActive = false;
		DamagedAble = false;
	}
}

void LivingObject::AddForce(Vector dir, float Power)
{
	acceleration += Vector(dir.x * Power, dir.y * Power);
}
