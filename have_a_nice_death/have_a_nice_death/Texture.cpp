#include "pch.h"
#include "Texture.h"
#include "DXBitmap.h"


Texture::~Texture()
{
	delete _bitmap;
	_bitmap = nullptr;
}


void Texture::Render(ID2D1RenderTarget* renderTarget, Vector pos, ImageAnchor drawAnchor, bool FlipOrder)
{
	if (_bitmap->GetBitmap() == nullptr)
		return;



	//비트 맵 상에서 가져올 영역 0.0 부터 끝까지.
	D2D1_RECT_F srcLeft = D2D1::RectF(
		0,
		0,
		static_cast<float>(_bitmap->GetBitmapSize().Width),
		static_cast<float>(_bitmap->GetBitmapSize().Height));

	D2D1_RECT_F destLeft;

	auto DrawBound = [this](ID2D1RenderTarget* renderTarget, D2D1_RECT_F& destLeft)
		{
			//디버그 모드용 경계면 그리기
			ID2D1SolidColorBrush* pBorderBrush = nullptr;
			renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBorderBrush);

			// 테두리 그리기
			renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f는 선 두께

			// 브러시 해제
			pBorderBrush->Release();
		};


	if (drawAnchor == ImageAnchor::Center)
	{
		float halfX = static_cast<float>(_bitmap->GetBitmapSize().Width) / 2;
		float halfY = static_cast<float>(_bitmap->GetBitmapSize().Height) / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y + halfY - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Bottomcenter)
	{
		float halfX = static_cast<float>(_bitmap->GetBitmapSize().Width) / 2;
		float height = static_cast<float>(_bitmap->GetBitmapSize().Height);

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - height - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Topleft)
	{
		destLeft = D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + static_cast<float>(_bitmap->GetBitmapSize().Width),
			pos.y + static_cast<float>(_bitmap->GetBitmapSize().Height));
	}

	else if (drawAnchor == ImageAnchor::Bottomright)
	{
		destLeft = D2D1::RectF(
			pos.x - static_cast<float>(_bitmap->GetBitmapSize().Width),
			pos.y - static_cast<float>(_bitmap->GetBitmapSize().Height),
			pos.x,
			pos.y);
	}

	//반전 그리기
	if (FlipOrder)
	{
		D2D1::Matrix3x2F oldTransform;
		renderTarget->GetTransform(&oldTransform);

		D2D1::Matrix3x2F flipMat =
			D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(pos.x, pos.y));

		renderTarget->SetTransform(flipMat * oldTransform);

		renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

		if (drawBound)
			DrawBound(renderTarget, destLeft);

		renderTarget->SetTransform(oldTransform);

	}

	//정방향
	else
	{
		renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

		if (drawBound)
			DrawBound(renderTarget, destLeft);
	}
}

void Texture::RenderSlope(ID2D1RenderTarget* renderTarget, Vector pos, float ratio, ImageAnchor drawAnchor)
{
	if (_bitmap->GetBitmap() == nullptr)
		return;

	if (ratio < 0.0f) ratio = 0.0f;
	if (ratio > 1.0f) ratio = 1.0f;

	float fullWidth = static_cast<float>(_bitmap->GetBitmapSize().Width);
	float fullHeight = static_cast<float>(_bitmap->GetBitmapSize().Height);


	//비트 맵 상에서 가져올 영역 0.0 부터 끝까지.
	D2D1_RECT_F srcLeft = D2D1::RectF(
		0,
		0,
		static_cast<float>(_bitmap->GetBitmapSize().Width),
		static_cast<float>(_bitmap->GetBitmapSize().Height));

	D2D1_RECT_F destLeft;

	if (drawAnchor == ImageAnchor::Center)
	{
		float halfX = (fullWidth * ratio )/ 2;
		float halfY = fullHeight / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y + halfY - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Bottomcenter)
	{
		float halfX = (fullWidth * ratio) / 2;
		float halfY = fullHeight / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Topleft)
	{
		destLeft = D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + (fullWidth * ratio),
			pos.y + fullHeight);
	}

	else if (drawAnchor == ImageAnchor::Bottomright)
	{
		destLeft = D2D1::RectF(
			pos.x - fullWidth * ratio,
			pos.y - fullHeight,
			pos.x,
			pos.y);
	}

	//D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
	//D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);


}
