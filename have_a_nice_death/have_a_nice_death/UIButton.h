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
		UiType = UiType::Button;

		if (name.find("CURSE") == std::string::npos)
		{
			_actionFunc = Game::GetInstance()->BindGameActionByName(name);
		}

		targetPos = pos;
		currentPos = targetPos;
		
	}

	~UIButton();

	virtual void Init() override;
	virtual void Update(float deltatime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;

	std::function<void()> _actionFunc;

	bool CheckClicked(Vector mousepos);
	void DoAction();
};

