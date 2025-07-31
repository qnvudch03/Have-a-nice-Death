#pragma once
#include "UI.h"

class Texture;

class UIImage : public UI
{

	using Super = UI;

public:

	UIImage(Texture* texture, Vector pos) : Super(texture, pos)
	{

	}

	~UIImage();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

