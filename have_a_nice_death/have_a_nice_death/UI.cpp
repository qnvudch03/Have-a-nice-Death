#include "pch.h"
#include "UI.h"

void UI::Render(ID2D1RenderTarget* renderTarget)
{
	_uiTexture->Render(renderTarget, _pos, DrawAnchor::Topleft);
}
