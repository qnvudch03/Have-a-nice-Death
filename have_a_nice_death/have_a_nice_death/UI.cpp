#include "pch.h"
#include "UI.h"

void UI::Render(ID2D1RenderTarget* renderTarget)
{
	if (_UiType == UiType::HP_Bar)
	{
		_uiTexture->RenderSlope(renderTarget, _pos, ratio, ImageAnchor::Topleft);
	}

	else
	{
		_uiTexture->Render(renderTarget, _pos, ImageAnchor::Topleft);
	}

}
