#include "pch.h"
#include "Texture.h"
#include "DXBitmap.h"


void Texture::Destroy()
{
}

void Texture::Render(ID2D1RenderTarget* renderTarget, Vector pos)
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
    D2D1_RECT_F destLeft = D2D1::RectF(
        pos.x,
        pos.y,
        pos.x + static_cast<float>(_bitmap->GetBitmapSize().Width),
        pos.y + static_cast<float>(_bitmap->GetBitmapSize().Height)
    );
    renderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);
}
