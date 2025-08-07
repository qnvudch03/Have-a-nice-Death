#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "Game.h"

void Object::Render(ID2D1RenderTarget* renderTarget)
{
	/*for (auto& iter : *_Playtextures)
	{
		iter->Render(renderTarget, GetPos());
	}*/
	_renderTarget = renderTarget;

	if(animator.GetAnimTexture() != nullptr)
		animator.GetAnimTexture()->Render(renderTarget, GetPos(), anchorPosition, renderingFlipOrder);

	//콜라더 그리기
	if (Game::GetInstance()->GetScene()->IsbugMode && collider != nullptr)
	{
		D2D1_RECT_F destLeft = D2D1::RectF(
			collider->Getrectangle().TopLeft.x,
			collider->Getrectangle().TopLeft.y,
			collider->Getrectangle().BottomRight.x,
			collider->Getrectangle().BottomRight.y);

		//디버그 모드용 경계면 그리기
		ID2D1SolidColorBrush* pBorderBrush = nullptr;
		_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBorderBrush);

		// 테두리 그리기
		_renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f는 선 두께

		// 브러시 해제
		pBorderBrush->Release();
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
	//Not called
	//animator.Destroy();
}

void Object::SetCollider()
{

}