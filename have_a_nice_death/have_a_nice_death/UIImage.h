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

		else if (name.find("BackGround") != std::string::npos)
		{
			_UiType = UiType::BackGround;
		}

		else
			_UiType = UiType::Image;

		_targetPos = pos;
		_currentPos = _targetPos;
	}

	~UIImage();

	virtual void Init() override;
	virtual void Update(float deltatime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
};

