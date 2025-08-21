#include "pch.h"
#include "Texture.h"
#include "DXBitmap.h"
#include "Game.h"


Texture::~Texture()
{
	delete _bitmap;
	_bitmap = nullptr;
}


void Texture::Render(ID2D1RenderTarget* renderTarget, Vector pos, ImageAnchor drawAnchor, bool FlipOrder)
{
	if (_bitmap->GetBitmap() == nullptr)
		return;

	DXBitmap* sellectedBitMap = _bitmap;

	if (renderTarget != _mainWindowRenderTarget)
	{
		if (_subbitmap == nullptr)
		{
			_subbitmap = new DXBitmap();
			_subbitmap->Load(renderTarget, FilePath);

			if (!_subbitmap->GetBitmap())
			{
				int apple = 10;
			}
		}

		sellectedBitMap = _subbitmap;
	}

	if (!sellectedBitMap->GetBitmap())
	{
		int apple = 10;
	}


	//비트 맵 상에서 가져올 영역 0.0 부터 끝까지.
	D2D1_RECT_F srcLeft = D2D1::RectF(
		0,
		0,
		static_cast<float>(sellectedBitMap->GetBitmapSize().Width),
		static_cast<float>(sellectedBitMap->GetBitmapSize().Height));

	/*D2D1_RECT_F srcLeft = D2D1::RectF(
		0,
		0,
		static_cast<float>(_textureSizeX),
		static_cast<float>(_textureSizeY));*/

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
		/*float halfX = static_cast<float>(_bitmap->GetBitmapSize().Width) / 2;
		float halfY = static_cast<float>(_bitmap->GetBitmapSize().Height) / 2;*/

		float halfX = _textureSizeX / 2;
		float halfY = _textureSizeY / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y + halfY - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Bottomcenter)
	{
		float halfX = _textureSizeX / 2;
		float height = _textureSizeY;

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
			pos.x + _textureSizeX,
			pos.y + _textureSizeY);
	}

	else if (drawAnchor == ImageAnchor::Bottomright)
	{
		destLeft = D2D1::RectF(
			pos.x - _textureSizeX,
			pos.y - _textureSizeY,
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

		renderTarget->DrawBitmap(sellectedBitMap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

		if (drawBound)
			DrawBound(renderTarget, destLeft);

		renderTarget->SetTransform(oldTransform);

	}

	//정방향
	else
	{
		renderTarget->DrawBitmap(sellectedBitMap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

		if (drawBound)
			DrawBound(renderTarget, destLeft);
	}
}

void Texture::RenderSlope(ID2D1RenderTarget* renderTarget, Vector pos, Vector ratio, ImageAnchor drawAnchor, bool FlipOrder)
{
	if (_bitmap->GetBitmap() == nullptr)
		return;

	if (ratio.x < 0.0f) ratio.x = 0.0f;
	if (ratio.y < 0.0f) ratio.y = 0.0f;

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
		float halfX = (fullWidth * ratio.x )/ 2;
		float halfY = (fullHeight * ratio.y) / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y + halfY - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Bottomcenter)
	{
		float halfX = (fullWidth * ratio.x) / 2;
		float halfY = (fullHeight * ratio.y) / 2;

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
			pos.x + (fullWidth * ratio.x),
			pos.y + fullHeight * ratio.y);
	}

	else if (drawAnchor == ImageAnchor::Bottomright)
	{
		destLeft = D2D1::RectF(
			pos.x - fullWidth * ratio.x,
			pos.y - fullHeight * ratio.y,
			pos.x,
			pos.y);
	}

	//D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
	//D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

}

void Texture::RenderCustomSize(ID2D1RenderTarget* renderTarget, Vector pos, Vector size, ImageAnchor drawAnchor, bool FlipOrder)
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
		/*float halfX = static_cast<float>(_bitmap->GetBitmapSize().Width) / 2;
		float halfY = static_cast<float>(_bitmap->GetBitmapSize().Height) / 2;*/

		float halfX = size.x / 2;
		float halfY = size.y / 2;

		destLeft = D2D1::RectF(
			pos.x - halfX - _renderingOffsetX,
			pos.y - halfY - _renderingOffsetY,
			pos.x + halfX - _renderingOffsetX,
			pos.y + halfY - _renderingOffsetY);
	}

	else if (drawAnchor == ImageAnchor::Bottomcenter)
	{
		float halfX = size.x / 2;
		float height = size.y;

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
			pos.x + size.x,
			pos.y + size.y);
	}

	else if (drawAnchor == ImageAnchor::Bottomright)
	{
		destLeft = D2D1::RectF(
			pos.x - size.x,
			pos.y - size.y,
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

void Texture::RenderWinOffset(ID2D1RenderTarget* renderTarget, Vector pos, ImageAnchor drawAnchor, Vector WinOffset)
{
	Vector newPos = Vector(pos.x + WinOffset.x, pos.y + WinOffset.y);
	Render(renderTarget, newPos, drawAnchor, false);
}
