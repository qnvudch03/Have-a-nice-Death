#include "pch.h"
#include "LivingObject.h"

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
	Super::Update(deltaTime);
}

void LivingObject::Destroy()
{
	Super::Destroy();
}

void LivingObject::SetState(std::string state)
{
	if (_ownTextures->find(state) == _ownTextures->end())
		return;

	SetPlayTexture(&(*_ownTextures)[state]);
}
