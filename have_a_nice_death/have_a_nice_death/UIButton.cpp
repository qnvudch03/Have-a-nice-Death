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
