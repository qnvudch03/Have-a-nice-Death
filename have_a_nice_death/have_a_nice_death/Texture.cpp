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


    //화면에 그릴 영역, 인자로 받은 위치 값으로부터, 이미지 끝까지(중앙 기준으로 그리게 할려면 수정이 필요)
    //그려지는건 DEATH 중심으로 그려져야 해, 이미지의 offset 값 만큼, 화면에서 그려질 영역에 더해 줘
    //예를들어 중심점에서 -50 pixel 만큼 뒤로 가는 애니메이션 모션이 있다면, 그냥 화면에 그릴 때 +50위치로 해 줘

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
    if(FlipOrder)
    {
        D2D1::Matrix3x2F oldTransform;
        renderTarget->GetTransform(&oldTransform); // 기존 행렬 저장

        // 중심 기준 좌우 반전 (pos.x가 이미지 중심)
        D2D1::Matrix3x2F flipMat =
            D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(pos.x, pos.y));

        // 변환 적용
        renderTarget->SetTransform(flipMat * oldTransform);

        // 이미지 그리기 (destRect는 기존처럼 작성)
        renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

        if (drawBound)
            DrawBound(renderTarget, destLeft);

        // 원래 상태로 되돌리기
        renderTarget->SetTransform(oldTransform);

    }
    
    //정방향
    else
    {
        renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

        if (drawBound)
            DrawBound(renderTarget, destLeft);
    }


    //if (drawBound)
    //{
    //    //디버그 모드용 경계면 그리기
    //    ID2D1SolidColorBrush* pBorderBrush = nullptr;
    //    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBorderBrush);

    //    // 테두리 그리기
    //    renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f는 선 두께

    //    // 브러시 해제
    //    pBorderBrush->Release();
    //}
        
    
}
