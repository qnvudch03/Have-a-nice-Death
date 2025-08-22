#include "pch.h"
#include "WindowMediator.h"
#include "Game.h"
#include "InputManager.h"
#include "StaticObject.h"
#include "SpriteManager.h"

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

	//������
	if (witch == 1)
	{
		//���������� ��Ŭ���� ���� ��� ����
	}

	//����
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
	if (indicator > 0)
	{
		//Load Next EditScene

	}

	else if (indicator < 0)
	{
		//Load Pre EditScene
	}
}

StaticObject* WindowMediator::MakePreViewObject(std::pair<std::string, std::string> RecievedData)
{
	const std::string& type = RecievedData.first;
	const std::string& name = RecievedData.second;

	if (type.empty() || name.empty())
	{
		delete preViewObject;
		preViewObject = nullptr;
		return nullptr;
	}

	delete preViewObject;
	preViewObject = nullptr;

	// 3. type�� �´� ��ü ����
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
