#include "pch.h"
#include "StaticObject.h"
#include "Collider.h"

void StaticObject::Init()
{
	Super::Init();
}

void StaticObject::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void StaticObject::Destroy()
{
	Super::Destroy();
}

void StaticObject::SetCollider()
{
	//플랫폼과, 캐릭터가 아니면 콜라이더를 할당하지 않음
	if (GetRenderLayer() != RenderLayer::Platform &&
		GetRenderLayer() != RenderLayer::Character)
	{
		return;
	}
	collider = new Collider(this, (*_ownTextures)[0]->GetTextureSize());
}
