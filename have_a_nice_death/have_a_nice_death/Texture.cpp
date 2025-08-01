#include "pch.h"
#include "Texture.h"
#include "DXBitmap.h"


Texture::~Texture()
{
    delete _bitmap;
    _bitmap = nullptr;
}


void Texture::Render(ID2D1RenderTarget* renderTarget, Vector pos, DrawAnchor drawAnchor)
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

    if (drawAnchor == DrawAnchor::Center)
    {
        float halfX = static_cast<float>(_bitmap->GetBitmapSize().Width) / 2;
        float halfY = static_cast<float>(_bitmap->GetBitmapSize().Height) / 2;

        destLeft = D2D1::RectF(
            pos.x - halfX - _renderingOffsetX,
            pos.y - halfY - _renderingOffsetY,
            pos.x + halfX - _renderingOffsetX,
            pos.y + halfY - _renderingOffsetY);
    }

    else if (drawAnchor == DrawAnchor::Topleft)
    {
        destLeft = D2D1::RectF(
            pos.x,
            pos.y,
            pos.x + static_cast<float>(_bitmap->GetBitmapSize().Width),
            pos.y + static_cast<float>(_bitmap->GetBitmapSize().Height));
    }

    else if (drawAnchor == DrawAnchor::Bottomright)
    {
        destLeft = D2D1::RectF(
            pos.x - static_cast<float>(_bitmap->GetBitmapSize().Width),
            pos.y - static_cast<float>(_bitmap->GetBitmapSize().Height),
            pos.x,
            pos.y);
    }
    
    renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);
}
