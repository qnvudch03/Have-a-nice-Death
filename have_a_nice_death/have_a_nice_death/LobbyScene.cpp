#include "pch.h"
#include "LobbyScene.h"
#include "SpriteManager.h"
#include "StaticObject.h"
#include "UIManager.h"
#include "UI.h"

void Lobby::Init()
{
	Super::Init();
}

void Lobby::Destroy()
{
	Super::Destroy();

}

void Lobby::Update(float deltatTime)
{
	Super::Update(deltatTime);
}

void Lobby::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void Lobby::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}

void Lobby::EraseScene()
{
	Super::EraseScene();

	for (auto Iter : LobbySceneObjects)
	{
		delete Iter;
	}
}

void Lobby::loadResource()
{

	auto setLobbyActor = [this](Object* actor)
		{
			LobbySceneObjects.push_back(actor);
			actor->animator.SetAnimSpeed(DefaultAnimSpeed);
		};

	//리소스 매니저에서, 필요한 Texture들을 가져오기 (배경 화면, 캐릭터, 시작버튼, 에디터 버튼)
	_backGround = new StaticObject(SpriteManager::GetInstance()->GetTextures("Home", "BackGround"), RenderLayer::Background, Vector(0, 0), ImageAnchor::Topleft);
	if (_backGround != nullptr)
	{
		setLobbyActor(_backGround);
	}

	_Death_Head = new StaticObject(SpriteManager::GetInstance()->GetTextures("Home", "head"), RenderLayer::Effect, Vector(GWinSizeX - 400, 280), ImageAnchor::Center);
	if (_Death_Head != nullptr)
	{
		//람다를 써 보자
		setLobbyActor(_Death_Head);
	}
		

	_Death_Body = new StaticObject(SpriteManager::GetInstance()->GetTextures("Home", "body"), RenderLayer::Character, Vector(GWinSizeX - 420, 550), ImageAnchor::Center);
	if (_Death_Body != nullptr)
	{
		setLobbyActor(_Death_Body);
	}
		

	_Death_Arm = new StaticObject(SpriteManager::GetInstance()->GetTextures("Home", "arm"), RenderLayer::Effect, Vector(GWinSizeX - 370, 520), ImageAnchor::Center);
	if (_Death_Arm != nullptr)
	{
		setLobbyActor(_Death_Arm);
	}
		
	_smoke = new StaticObject(SpriteManager::GetInstance()->GetTextures("Home", "Smoke"), RenderLayer::Effect, Vector(GWinSizeX - 425, 445), ImageAnchor::Bottomright);
	if (_smoke != nullptr)
	{
		setLobbyActor(_smoke);
	}


	for (auto& Iter : LobbySceneObjects)
	{
		ReserveAdd(Iter);
	}


}

void Lobby::loadUI()
{
	//LobbySceneUI = UIManager::GetInstance()->GetSceneUI(this);
	SceneUI = UIManager::GetInstance()->GetSceneUI(this);

	for (auto& lobbyUI : *SceneUI)
	{
		lobbyUI->SetOpen(true);
	}
}
