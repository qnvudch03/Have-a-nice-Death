#include "pch.h"
#include "LivingObject.h"
#include "Controller.h"
#include "Collider.h"
#include "Game.h"
#include "Scene.h"

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

	Super::Update(deltaTime);

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
	if (ownTextures->find("Ideal") == ownTextures->end())
		return;

	//첫 ideal 모션의 크기를 가져와 collider로 설정한다.
	collider = new Collider(this, (*ownTextures)["Ideal"][0]->GetTextureSize());
}

void LivingObject::SetState(std::string state, bool IsLoop)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	SetAnimaotrTextures(&(*ownTextures)[state], IsLoop);
}

void LivingObject::ApplyEnvironment(float deltaTime)
{
	acceleration = { 0,0 };
	velocity.x *= 0.98;

	if (!isGround)
	{
		acceleration += AddForce(Vector(0, 1), gravityPower);
	}

	if (isCanMove && !isTurning)
	{
		Vector inPut = { 0,0 };
		KeyType currentInput = _controller->GetInput();

		if (currentInput == KeyType::Move)
		{
			inPut.x = forwordDirection;
		}

		/*	else if (currentInput == KeyType::Left)
			{
				inPut.x = -1;
			}*/

		else if (currentInput == KeyType::SpaceBar)
		{
			acceleration += AddForce(Vector(0, -1), objectStat.jumpPower);
		}

		acceleration += AddForce(inPut, objectStat.moveForce);

		velocity += acceleration * deltaTime;
	}

	Vector currentPos = GetPos();
	Vector movedPos = currentPos + velocity;

	if (checkCollision(this, currentPos, movedPos))
	{
		SetPos(movedPos);
	}

	

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
