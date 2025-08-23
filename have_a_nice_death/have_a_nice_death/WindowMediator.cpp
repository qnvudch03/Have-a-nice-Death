#include "pch.h"
#include "WindowMediator.h"
#include "Game.h"
#include "InputManager.h"
#include "StaticObject.h"
#include "SpriteManager.h"

#include "EditorScene.h"

void WindowMediator::ReFresh()
{
	if (Activate == false)
	{
		game = Game::GetInstance();

		if (game == nullptr)
			return;

		editScene = dynamic_cast<EditorScene*>(game->GetCurrentScence());

		if (editScene == nullptr)
			return;

		Activate = true;

		return;
	}

	else
	{
		if (preViewObject != nullptr)
		{
			editScene->ReserveRemove(preViewObject);
			//preViewObject = nullptr;
		}
	}

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
	if (witch == 1)
	{
		//서브윈도우 우클릭은 딱히 기능 없음
	}

	//왼쪽
	else if (witch == -1)
	{
		std::pair<std::string, std::string> RecievedData;
		RecievedData = editScene->GetSellectedEdiSceneObjectData();

		editScene->SetPrieViewObject(RecievedData, MakePreViewObject(RecievedData));
	}
}

void WindowMediator::OnSubWinMouseWhillUp(int witch)
{
	//8
	if (witch == 2)
	{
		editScene->AddWinOffset(Vector(0, -50));
	}

	else if (witch == 8)
	{
		editScene->AddWinOffset(Vector(0, 50));
	}
}

void WindowMediator::OnMultiplyBtnPressed()
{
	editScene->ChangeColor();
}

void WindowMediator::OnPlusMinusPressed(int indicator)
{
	editScene->ChangeStage(indicator);
}

void WindowMediator::OnStageReRoaded()
{

}

StaticObject* WindowMediator::MakePreViewObject(std::pair<std::string, std::string> RecievedData)
{
	const std::string type = RecievedData.first;
	const std::string name = RecievedData.second;

	if (type.empty() || name.empty())
	{
		return nullptr;
	}

	if (preViewObject != nullptr)
	{
		delete preViewObject;
		preViewObject = nullptr;
	}

	// 3. type에 맞는 객체 생성
	if (type == "Player" || type == "AI")
	{
		preViewObject = new StaticObject(
			SpriteManager::GetInstance()->GetTextures(name, "Idle"),
			RenderLayer::Character,
			Vector(0, 0),
			ImageAnchor::Bottomcenter
		);
		SetCustumAnimSpeed(name, preViewObject);
	}
	else if (type == "Platform")
	{
		preViewObject = new StaticObject(
			SpriteManager::GetInstance()->GetTextures(type, name),
			RenderLayer::Platform,
			Vector(0, 0),
			ImageAnchor::Center
		);
	}

	return preViewObject;

}

void WindowMediator::SetCustumAnimSpeed(std::string name, StaticObject* obj)
{
	if (!name.compare("Death"))
	{
		obj->animator.SetAnimSpeed(30);
		return;
	}
	else if (!name.compare("SmallGhost"))
	{
		obj->animator.SetAnimSpeed(10);
		return;
	}
	else if (!name.compare("MedGhost"))
	{
		obj->animator.SetAnimSpeed(10);
		return;
	}
}
