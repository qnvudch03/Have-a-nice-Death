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

	//�ݶ�� �׸���
	if (Game::GetInstance()->GetScene()->IsbugMode && collider != nullptr)
	{
		D2D1_RECT_F destLeft = D2D1::RectF(
			collider->Getrectangle().TopLeft.x,
			collider->Getrectangle().TopLeft.y,
			collider->Getrectangle().BottomRight.x,
			collider->Getrectangle().BottomRight.y);

		//����� ���� ���� �׸���
		ID2D1SolidColorBrush* pBorderBrush = nullptr;
		_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pBorderBrush);

		// �׵θ� �׸���
		_renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f�� �� �β�

		// �귯�� ����
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