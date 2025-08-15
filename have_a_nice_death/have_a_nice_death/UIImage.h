#pragma once
#include "UI.h"

class Texture;

class UIImage : public UI
{

	using Super = UI;

public:

	UIImage(std::string name, Texture* texture, Vector pos) : Super(name, texture, pos)
	{
		if (!name.compare("HPbar_body"))
		{
			_UiType = UiType::HP_Bar;
		}

		else
			_UiType = UiType::Image;
	}

	~UIImage();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
};

