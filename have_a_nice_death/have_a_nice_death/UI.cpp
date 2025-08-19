#include "pch.h"
#include "UI.h"

void UI::Render(ID2D1RenderTarget* renderTarget)
{
	if (_UiType == UiType::HP_Bar || _UiType == UiType::BackGround)
	{
		_uiTexture->RenderSlope(renderTarget, _currentPos, ratio, ImageAnchor::Topleft);
	}

	else
	{
		_uiTexture->Render(renderTarget, _currentPos, ImageAnchor::Topleft);
	}

}

void UI::Update(float deltatime)
{
	if (_isMoveable == false ||
		_currentPos == _targetPos)
	{
		return;
	}
		

	_currentPos.x += movingDirect.x * deltatime * movingSpeed;
	_currentPos.y += movingDirect.y * deltatime * movingSpeed;

	if (_currentPos.x < _targetPos.x)
		_currentPos.x = _targetPos.x;

	if (_currentPos.y < _targetPos.y)
		_currentPos.y = _targetPos.y;
}
