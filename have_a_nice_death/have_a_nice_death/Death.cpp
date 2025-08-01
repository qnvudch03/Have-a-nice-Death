#include "pch.h"
#include "Death.h"

void Death::Init()
{
	Super::Init();
	SetState("Ideal");
}

void Death::Update(float deltaTime)
{
	Super::Update(deltaTime);
	//TODO
	//매 업데이트 마다, 입력 값을 받아서 상태를 갱신, 그리고 상태를 보내줌
	// 혹시 상태마다 애니메이션 스피드가 다를 수도 있음
	//animaotr.SetAnimSpeed(30);
	//SetState("Ideal");
}

void Death::Destroy()
{
}
