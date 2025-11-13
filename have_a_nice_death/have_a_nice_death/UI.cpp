#include "pch.h"
#include "UI.h"

void UI::Render(ID2D1RenderTarget* renderTarget)
{
	if (UiType == UiType::HP_Bar || UiType == UiType::BackGround)
	{
		uiTexture->RenderSlope(renderTarget, currentPos, ratio, ImageAnchor::Topleft);
	}

	else
	{
		uiTexture->Render(renderTarget, currentPos, ImageAnchor::Topleft);
	}

}

void UI::Update(float deltatime)
{
	if (_isMoveable == false ||
		currentPos == targetPos)
	{
		return;
	}
		

	currentPos.x += movingDirect.x * deltatime * movingSpeed;
	currentPos.y += movingDirect.y * deltatime * movingSpeed;

	if (currentPos.x < targetPos.x)
		currentPos.x = targetPos.x;

	if (currentPos.y < targetPos.y)
		currentPos.y = targetPos.y;
}
