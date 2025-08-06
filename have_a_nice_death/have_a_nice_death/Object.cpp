#include "pch.h"
#include "Object.h"
#include "Texture.h"

void Object::Render(ID2D1RenderTarget* renderTarget)
{
	/*for (auto& iter : *_Playtextures)
	{
		iter->Render(renderTarget, GetPos());
	}*/

	if(animator.GetAnimTexture() != nullptr)
		animator.GetAnimTexture()->Render(renderTarget, GetPos(), anchorPosition, renderingFlipOrder);

}

void Object::SetDebugMode(bool debugMode)
{
	//animator.GetAnimTexture()->SetDrawBound(debugMode);
	for (auto& iter : *animator.GetAnimTextureVec())
	{
		iter->SetDrawBound(debugMode);
	}
}

void Object::Update(float deltaTime)
{
	animator.Update(deltaTime);
}

void Object::Destroy()
{
	animator.Destroy();
}