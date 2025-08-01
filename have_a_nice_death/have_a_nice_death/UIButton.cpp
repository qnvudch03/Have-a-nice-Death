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
	//���� UI�� �⺻������ ������� �����̶�� �����ϰ� �ڵ带 ¥�� �ִµ�, ���߿� Anchor ��ġ �޾ƿͼ� �۾� �� �ʿ䵵 ������ �ؾ� ��
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
