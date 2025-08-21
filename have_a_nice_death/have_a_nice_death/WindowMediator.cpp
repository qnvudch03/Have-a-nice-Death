#include "pch.h"
#include "WindowMediator.h"
#include "Game.h"
#include "InputManager.h"

#include "EditorScene.h"

void WindowMediator::ReFresh()
{
	game = Game::GetInstance();

	if (game == nullptr)
		return;

	editScene = dynamic_cast<EditorScene*>(game->GetCurrentScence());

	if (editScene == nullptr)
		return;

	Activate = true;
}

void WindowMediator::Update(float deltatime)
{
	if (Activate == false)
		return;
}

void WindowMediator::OnSubWinClicked(int witch, Vector pos)
{
	editScene->subWinMouseClickedPos = pos;

	//오른쪽
	if(witch == 1)
	{
		
	}

	//왼쪽
	else if (witch == -1)
	{
		std::pair<std::string, std::string> RecievedData;
		RecievedData = editScene->GetSellectedEdiSceneObjectData();

	}
}

void WindowMediator::OnSubWinNumPressed(int witch)
{
	//8
	if (witch == 8)
	{
		if (InputManager::GetInstance()->GetButtonUp(KeyType::NumPad8))
		{
			editScene->AddWinOffset(Vector(0, -50));
		}
		
	}

	else if (witch == 2)
	{
		if (InputManager::GetInstance()->GetButtonUp(KeyType::NumPad2))
		{
			editScene->AddWinOffset(Vector(0, 50));
		}
		
	}
}

void WindowMediator::OnMouseWhillMove(bool num)
{
	editScene->ChangeColor(num);
}
