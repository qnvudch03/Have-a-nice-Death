#include "pch.h"
#include "LobbyScene.h"
#include "ResourceManager.h"
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

void Lobby::loadResource()
{

	auto setLobbyActor = [this](Object* actor)
		{
			LobbySceneObjects.push_back(actor);
			actor->animaotr.SetAnimSpeed(30);
		};

	//���ҽ� �Ŵ�������, �ʿ��� Texture���� �������� (��� ȭ��, ĳ����, ���۹�ư, ������ ��ư)
	_backGround = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "BackGround"), RenderLayer::Background, Vector(0, 0), DrawAnchor::Topleft);
	if (_backGround != nullptr)
	{
		setLobbyActor(_backGround);
	}

	_Death_Head = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "head"), RenderLayer::Effect, Vector(GWinSizeX - 400, 280), DrawAnchor::Center);
	if (_Death_Head != nullptr)
	{
		//���ٸ� �� ����
		setLobbyActor(_Death_Head);
	}
		

	_Death_Body = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "body"), RenderLayer::Character, Vector(GWinSizeX - 400, 550), DrawAnchor::Center);
	if (_Death_Body != nullptr)
	{
		setLobbyActor(_Death_Body);
	}
		

	_Death_Arm = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "arm"), RenderLayer::Effect, Vector(GWinSizeX - 350, 510), DrawAnchor::Center);
	if (_Death_Arm != nullptr)
	{
		setLobbyActor(_Death_Arm);
	}
		
	_smoke = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "Smoke"), RenderLayer::Effect, Vector(GWinSizeX - 410, 435), DrawAnchor::Bottomright);
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
}
