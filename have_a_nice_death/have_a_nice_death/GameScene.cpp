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
	//LoadResoucle랑 LoadUI랑 하고 게임 씬은 텍스트에서 stage 파일 읽어서 정보를 얻어와야 해
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

	//리소스 매니저에서, 필요한 Texture들을 가져오기 (배경 화면, 캐릭터, 시작버튼, 에디터 버튼)
	// TODO
	//여기서 싹 다 가져오고, LoadStage에서 그때 addreserve 하자
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
