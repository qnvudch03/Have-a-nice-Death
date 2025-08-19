#include "pch.h"
#include "UIButton.h"

UIButton::~UIButton()
{
	delete _uiTexture;
}

void UIButton::Init()
{

}

void UIButton::Update(float deltatime)
{
	Super::Update(deltatime);
}

void UIButton::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}

bool UIButton::CheckClicked(Vector mousepos)
{
	//TODO
	//현재 UI는 기본적으로 좌측상단 고정이라고 생각하고 코드를 짜고 있는데, 나중에 Anchor 위치 받아와서 작업 할 필요도 있으면 해야 함
	Vector UIPos = _currentPos;
	Vector UISize = _uiTexture->GetTextureSize();

	if (
		(mousepos.x > _currentPos.x && mousepos.x < _currentPos.x + UISize.x) &&
		(mousepos.y > _currentPos.y && mousepos.y < _currentPos.y + UISize.y)

		)
	{
		return true;
	}

	return false;
}

void UIButton::DoAction()
{
	if (_actionFunc == nullptr)
		return;

	_actionFunc();
}
