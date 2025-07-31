#pragma once
#include "UI.h"

class Texture;

class UIButton : public UI
{

	using Super = UI;

public:

	UIButton(Texture* texture, Vector pos) : Super(texture, pos)
	{

	}
	~UIButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
};

