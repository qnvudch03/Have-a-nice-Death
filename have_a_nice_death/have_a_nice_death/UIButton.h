#pragma once
#include "UI.h"
#include "Game.h"

class Texture;

class UIButton : public UI
{

	using Super = UI;

public:

	UIButton(std::string name, Texture* texture, Vector pos) : Super(name, texture, pos)
	{
		_UiType = UiType::Button;

		_actionFunc = Game::GetInstance()->BindingActionByName(name);
	}

	~UIButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;

	std::function<void()> _actionFunc;

	bool CheckClicked(Vector mousepos);
	void DoAction();
};

