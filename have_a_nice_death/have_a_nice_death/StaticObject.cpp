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
	//�÷�����, ĳ���Ͱ� �ƴϸ� �ݶ��̴��� �Ҵ����� ����
	if (GetRenderLayer() != RenderLayer::Platform &&
		GetRenderLayer() != RenderLayer::Character)
	{
		return;
	}
	collider = new Collider(this, (*_ownTextures)[0]->GetTextureSize());
}
