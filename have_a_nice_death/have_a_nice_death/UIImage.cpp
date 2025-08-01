#include "pch.h"
#include "UIImage.h"

UIImage::~UIImage()
{
	delete _uiTexture;
}

void UIImage::Init()
{
}

void UIImage::Update()
{
}

void UIImage::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}
