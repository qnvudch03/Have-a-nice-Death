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
			UiType = UiType::HP_Bar;
		}

		else if (name.find("BackGround") != std::string::npos)
		{
			UiType = UiType::BackGround;
		}

		else
			UiType = UiType::Image;

		targetPos = pos;
		currentPos = targetPos;
	}

	~UIImage();

	virtual void Init() override;
	virtual void Update(float deltatime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
};

