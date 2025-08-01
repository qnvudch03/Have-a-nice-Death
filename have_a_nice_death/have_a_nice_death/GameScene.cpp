#include "pch.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "LivingObject.h"
#include "SpriteManager.h"
#include "Death.h"

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

	for (auto Iter : _gameSceneObjects)
	{
		delete Iter.second;
	}
	_gameSceneObjects.clear();
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
