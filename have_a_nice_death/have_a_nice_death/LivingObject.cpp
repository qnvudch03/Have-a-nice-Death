#include "pch.h"
#include "LivingObject.h"
#include "Controller.h"

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

	acceleration = { 0,0 };
	velocity *= 0.98;

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
			acceleration += AddForce(Vector(0,-1), objectStat.jumpPower);
		}

		acceleration += AddForce(inPut, objectStat.moveForce);

		velocity += acceleration * deltaTime;
	}

	Vector pos = GetPos();

	SetPos(pos + velocity);
	
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

void LivingObject::SetState(std::string state, bool IsLoop)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	SetAnimaotrTextures(&(*ownTextures)[state], IsLoop);
}

Vector LivingObject::AddForce(Vector dir, float Power)
{
	return Vector(dir.x * Power, dir.y * Power);
}
