#include "pch.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "LivingObject.h"
#include "SpriteManager.h"
#include "Death.h"
#include "Controller.h"

void GameScene::Init()
{
	Super::Init();

	//TODO
	//LoadResoucle�� LoadUI�� �ϰ� ���� ���� �ؽ�Ʈ���� stage ���� �о ������ ���;� ��
}

void GameScene::Destroy()
{
	Super::Destroy();
}

void GameScene::Update(float deltatTime)
{
	Super::Update(deltatTime);
}

void GameScene::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void GameScene::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
}

void GameScene::EraseScene()
{
	Super::EraseScene();

	if (_gameSceneObjects.empty())
		return;

	for (auto gmaeObj : _gameSceneObjects)
	{
		delete gmaeObj.second;
	}
	_gameSceneObjects.clear();

	//��Ʈ�ѷ� ����
	for (auto gamdController : _gameControllerMap)
	{
		delete gamdController.second;
	}
}



void GameScene::loadResource()
{
	_gameSceneObjects.clear();


	auto setGameActor = [this](Object* actor, std::string objectName)
		{
			_gameSceneObjects[objectName] = actor;
			actor->animaotr.SetAnimSpeed(30);
		};

	//���ҽ� �Ŵ�������, �ʿ��� Texture���� �������� (��� ȭ��, ĳ����, ���۹�ư, ������ ��ư)
	// TODO
	//���⼭ �� �� ��������, LoadStage���� �׶� addreserve ����
	_gameSceneObjects[GameSceneObject::Death] = new Death(SpriteManager::GetInstance()->GetTextureMap("Death"), RenderLayer::Character, DrawAnchor::Center);


	for (auto& obj : _gameSceneObjects)
	{
		ReserveAdd(obj.second);
	}
}

void GameScene::loadUI()
{
	//HPbar
}

void GameScene::AddController(LivingObject* ownerObject, Controller* controller)
{
	if (_gameControllerMap.find(ownerObject) == _gameControllerMap.end())
		return;

	_gameControllerMap.insert(std::make_pair(ownerObject, controller));
	controller->SetOwner(ownerObject);
}

void GameScene::ChangeControllerOwner(LivingObject* newownerObject, Controller* controller)
{
	LivingObject* PostOwner = controller->GetOwner();

	if (PostOwner == nullptr || _gameControllerMap.find(PostOwner) == _gameControllerMap.end())
		return;

	_gameControllerMap.erase(PostOwner);

	AddController(newownerObject, controller);
}
