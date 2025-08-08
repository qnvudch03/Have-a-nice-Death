#include "pch.h"
#include "SmallGhost.h"

void SmallGhost::Init()
{
	Super::Init();

	SetState("Idle");
	//state = EDeathStatepriority::State_Idle;
	animator.SetAnimSpeed(15);
}

void SmallGhost::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void SmallGhost::Destroy()
{
	Super::Destroy();
}

void SmallGhost::OnAnimEnd()
{
}
