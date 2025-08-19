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
	//���� UI�� �⺻������ ������� �����̶�� �����ϰ� �ڵ带 ¥�� �ִµ�, ���߿� Anchor ��ġ �޾ƿͼ� �۾� �� �ʿ䵵 ������ �ؾ� ��
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
