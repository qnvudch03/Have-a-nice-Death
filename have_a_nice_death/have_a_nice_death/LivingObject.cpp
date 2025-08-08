#include "pch.h"
#include "LivingObject.h"
#include "Controller.h"
#include "Collider.h"
#include "Game.h"
#include "DebugLenderer.h"

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

void LivingObject::SetState(std::string state, bool IsLoop)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	SetAnimaotrTextures(&(*ownTextures)[state], IsLoop);
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

	Vector currentPos = GetPos();
	Vector movedPos = currentPos + velocity;

	SetPos(movedPos);

	collider->Update();
}

bool LivingObject::checkCollision(LivingObject* object, Vector start, Vector end)
{
	auto sceneActors = *Game::GetInstance()->GetCurrentScence()->GetActors();
	float tMin = FLT_MAX;

	for (auto& iter : sceneActors)
	{
		//플랫폼 외 모두 제외
		if (iter->GetRenderLayer() != RenderLayer::Platform)
			continue;

		RectanglePos collisionPos = iter->collider->Getrectangle();

		float t = 0.f;
		Vector normal;
		Vector hitPos;

		/*if (LineIntersectsAABB(start, end, rect, normal, hitPos, t))
		{

		}*/
	}

	return false;
}

Vector LivingObject::AddForce(Vector dir, float Power)
{
	return Vector(dir.x * Power, dir.y * Power);
}
