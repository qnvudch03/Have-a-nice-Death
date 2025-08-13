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
		_controller->Update();

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

void LivingObject::SetState(std::string state, bool IsLoop, int32 atkIndex)
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

void LivingObject::Die()
{
	Game::GetGameScene()->ReserveRemove(this);
}

void LivingObject::ApplyEnvironment(float deltaTime)
{
	Vector inPut = { 0,0 };
	acceleration = { 0,0 };
	velocity.x *= 0.98;

	KeyType currentInput = _controller->GetInput();

	if (abs(velocity.x) < 0.01)
	{
		velocity.x = 0;
	}

	if (abs(velocity.y) < 0.01)
	{
		velocity.y = 0;
	}

	if (groundSensor->IsActive())
	{
		//속도가 아래 방향일 경우에만 적용
		if(velocity.y > 0)
			velocity.y = 0;
	}

	else
	{
		if(isEffectGravity)
			acceleration += AddForce(Vector(0, 1), gravityPower);
	}

	if (isCanMove && !isTurning)
	{
		if (currentInput == KeyType::Move)
		{
			inPut.x = forwordDirection;
		}

		/*	else if (currentInput == KeyType::Left)
			{
				inPut.x = -1;
			}*/

		acceleration += AddForce(inPut, objectStat.moveForce);

		//공중상태에서는 가속도를 살짝 낮추자
		if (!groundSensor->IsActive())
			acceleration.x *= 0.8;
	}

	if (isCanJump)
	{
		if (currentInput == KeyType::SpaceBar)
		{
			if (groundSensor->IsActive())
				acceleration += AddForce(Vector(0, -1), objectStat.jumpPower);
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

void LivingObject::OnHitted(HitBox* hitbox)
{
	if (!DamagedAble)
		return;

	DamagedAble = false;
	isCanMove = false;
	isCanJump = false;

	TimeManager::GetInstance()->AddTimer(Timer([this]()
		{
			DamagedAble = true;
			isCanMove = true;
			isCanJump = true;
		},
		0.5));

	velocity.x = 0;

	if (forwordDirection == hitbox->GetForwordDirection())
	{
		forwordDirection *= -1;

		renderingFlipOrder = (forwordDirection == -1) ? true : (forwordDirection == 1) ? false : renderingFlipOrder;
	}

	TakeDamage(hitbox->damage);
}

void LivingObject::TakeDamage(float Damage)
{
	float damageAmount = (Damage - objectStat.def <= 0) ? 0 : Damage - objectStat.def;
	objectStat.hp -= damageAmount;

	if (objectStat.hp <= 0)
	{
		animator.ResetAnimTimer(20);
		SetState("Death", false);
		IsActive = false;
	}
}

Vector LivingObject::AddForce(Vector dir, float Power)
{
	return Vector(dir.x * Power, dir.y * Power);
}
