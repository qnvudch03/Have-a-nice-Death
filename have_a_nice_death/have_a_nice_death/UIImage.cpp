#include "pch.h"
#include "UIImage.h"

UIImage::~UIImage()
{
	delete _uiTexture;
}

void UIImage::Init()
{
}

void UIImage::Update(float deltatime)
{
	Super::Update(deltatime);
}

void UIImage::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}
