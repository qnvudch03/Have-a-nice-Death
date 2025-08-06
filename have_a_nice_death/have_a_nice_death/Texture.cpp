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



    //��Ʈ �� �󿡼� ������ ���� 0.0 ���� ������.
    D2D1_RECT_F srcLeft = D2D1::RectF(
        0,
        0,
        static_cast<float>(_bitmap->GetBitmapSize().Width),
        static_cast<float>(_bitmap->GetBitmapSize().Height));


    //ȭ�鿡 �׸� ����, ���ڷ� ���� ��ġ �����κ���, �̹��� ������(�߾� �������� �׸��� �ҷ��� ������ �ʿ�)
    //�׷����°� DEATH �߽����� �׷����� ��, �̹����� offset �� ��ŭ, ȭ�鿡�� �׷��� ������ ���� ��
    //������� �߽������� -50 pixel ��ŭ �ڷ� ���� �ִϸ��̼� ����� �ִٸ�, �׳� ȭ�鿡 �׸� �� +50��ġ�� �� ��

    D2D1_RECT_F destLeft;

    auto DrawBound = [this](ID2D1RenderTarget* renderTarget, D2D1_RECT_F& destLeft)
        {
            //����� ���� ���� �׸���
            ID2D1SolidColorBrush* pBorderBrush = nullptr;
            renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBorderBrush);

            // �׵θ� �׸���
            renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f�� �� �β�

            // �귯�� ����
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

    //���� �׸���
    if(FlipOrder)
    {
        D2D1::Matrix3x2F oldTransform;
        renderTarget->GetTransform(&oldTransform); // ���� ��� ����

        // �߽� ���� �¿� ���� (pos.x�� �̹��� �߽�)
        D2D1::Matrix3x2F flipMat =
            D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(pos.x, pos.y));

        // ��ȯ ����
        renderTarget->SetTransform(flipMat * oldTransform);

        // �̹��� �׸��� (destRect�� ����ó�� �ۼ�)
        renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

        if (drawBound)
            DrawBound(renderTarget, destLeft);

        // ���� ���·� �ǵ�����
        renderTarget->SetTransform(oldTransform);

    }
    
    //������
    else
    {
        renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);

        if (drawBound)
            DrawBound(renderTarget, destLeft);
    }


    //if (drawBound)
    //{
    //    //����� ���� ���� �׸���
    //    ID2D1SolidColorBrush* pBorderBrush = nullptr;
    //    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBorderBrush);

    //    // �׵θ� �׸���
    //    renderTarget->DrawRectangle(destLeft, pBorderBrush, 2.0f); // 2.0f�� �� �β�

    //    // �귯�� ����
    //    pBorderBrush->Release();
    //}
        
    
}
