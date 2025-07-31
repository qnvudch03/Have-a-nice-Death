#include "pch.h"
#include "LobbyScene.h"
#include "ResourceManager.h"
#include "StaticObject.h"

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
	_backGround = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "BackGround"), RenderLayer::Background);
	if (_backGround != nullptr)
	{
		/*LobbySceneObjects.push_back(_backGround);
		_backGround->animaotr.SetAnimSpeed(30);*/
		setLobbyActor(_backGround);
	}

	_Death_Head = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "head"), RenderLayer::Effect, Vector(GWinSizeX - 400, 300), true);
	if (_Death_Head != nullptr)
	{
		/*LobbySceneObjects.push_back(_Death_Head);
		_Death_Head->animaotr.SetAnimSpeed(30);*/

		//���ٸ� �� ����
		setLobbyActor(_Death_Head);
	}
		

	_Death_Body = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "body"), RenderLayer::Character, Vector(GWinSizeX - 400, 550), true);
	if (_Death_Body != nullptr)
	{
		/*LobbySceneObjects.push_back(_Death_Body);
		_Death_Body->animaotr.SetAnimSpeed(30);*/

		setLobbyActor(_Death_Body);
	}
		

	_Death_Arm = new StaticObject(ResourceManager::GetInstance()->GetTextures("Home", "arm"), RenderLayer::Effect, Vector(GWinSizeX - 350, 510), true);
	if (_Death_Arm != nullptr)
	{
		/*LobbySceneObjects.push_back(_Death_Arm);
		_Death_Arm->animaotr.SetAnimSpeed(30);*/

		setLobbyActor(_Death_Arm);
	}
		

	for (auto& Iter : LobbySceneObjects)
	{
		ReserveAdd(Iter);
	}


}
