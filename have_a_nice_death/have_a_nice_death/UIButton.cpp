#include "pch.h"
#include "UIButton.h"

UIButton::~UIButton()
{
	delete _uiTexture;
}

void UIButton::Init()
{

}

void UIButton::Update()
{
}

void UIButton::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}

bool UIButton::CheckClicked(Vector mousepos)
{
	//TODO
	//현재 UI는 기본적으로 좌측상단 고정이라고 생각하고 코드를 짜고 있는데, 나중에 Anchor 위치 받아와서 작업 할 필요도 있으면 해야 함
	Vector UIPos = _pos;
	Vector UISize = _uiTexture->GetTextureSize();

	if (
		(mousepos.x > _pos.x && mousepos.x < _pos.x + UISize.x) &&
		(mousepos.y > _pos.y && mousepos.y < _pos.y + UISize.y)

		)
	{
		return true;
	}

	return false;
}

void UIButton::DoAction()
{
	_actionFunc();
}
