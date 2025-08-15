#include "pch.h"
#include "DebugLenderer.h"
#include "Sensor.h"
#include "Collider.h"
#include "HitBox.h"
#include "Object.h"

void DebugLenderer::DrawReserved()
{
	if (!sensorVec.empty())
	{
		for (auto& iter : sensorVec)
		{
			DrawRenctangle(iter->GetRecPos().TopLeft, iter->GetRecPos().BottomRight, D2D1::ColorF::Blue);
		}

		sensorVec.clear();
	}

	if (!colliderVec.empty())
	{
		for (auto& iter : colliderVec)
		{
			DrawRenctangle(iter->Getrectangle().TopLeft, iter->Getrectangle().BottomRight, D2D1::ColorF::Green);
		}

		colliderVec.clear();
	}

	if (!hitBoxVec.empty())
	{
		for (auto& iter : hitBoxVec)
		{
			Vector hitBoxPos = iter->GetPos();
			Vector hitBoxSize = iter->GetSize();

			DrawRenctangle(Vector(hitBoxPos.x - hitBoxSize.x, hitBoxPos.y - hitBoxSize.y),
				Vector(hitBoxPos.x + hitBoxSize.x, hitBoxPos.y + hitBoxSize.y), D2D1::ColorF::Yellow);
		}

		hitBoxVec.clear();
	}

	/*if (!objVec.empty())
	{
		for (auto& iter : objVec)
		{
			Vector objpos = iter->GetPos();
			Vector textureSize = iter->animator.GetAnimTexture()->GetTextureSize();

			DrawRenctangle(Vector(objpos.x - textureSize.x * 0.5, objpos.y - textureSize.y),
				Vector(objpos.x + textureSize.x * 0.5, objpos.y), D2D1::ColorF::Red);
		}

		objVec.clear();
	}*/
	
}

void DebugLenderer::DrawRenctangle(Vector TopLeftPos, Vector BootomRightPos, D2D1::ColorF color, float Linewidth)
{
	D2D1_RECT_F destLeft = D2D1::RectF(
		TopLeftPos.x,
		TopLeftPos.y,
		BootomRightPos.x,
		BootomRightPos.y);

	//디버그 모드용 경계면 그리기
	ID2D1SolidColorBrush* pBorderBrush = nullptr;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &pBorderBrush);

	// 테두리 그리기
	renderTarget->DrawRectangle(destLeft, pBorderBrush, Linewidth); // 2.0f는 선 두께

	// 브러시 해제
	pBorderBrush->Release();
}
