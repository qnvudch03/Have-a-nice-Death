#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "Game.h"
#include "DebugLenderer.h"

void Object::Render(ID2D1RenderTarget* renderTarget)
{
	/*for (auto& iter : *_Playtextures)
	{
		iter->Render(renderTarget, GetPos());
	}*/

	if(animator.GetAnimTexture() != nullptr)
		animator.GetAnimTexture()->Render(renderTarget, GetPos(), anchorPosition, renderingFlipOrder);

	if (Game::GetInstance()->GetScene()->IsDbugMode && collider != nullptr)
	{
		//디버그 드로우 예약
		Game::GetInstance()->GetDebugLenderer()->ReserveCollider(collider);
	}


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
	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}
		
}

void Object::SetCollider()
{

}
