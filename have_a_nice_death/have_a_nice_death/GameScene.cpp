#include "pch.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "LivingObject.h"
#include "SpriteManager.h"
#include "Death.h"
#include "Controller.h"
#include "PlayerController.h"
#include "HitBoxManager.h"
#include "AnimHitBox.h"

void GameScene::Init()
{
	Super::Init();

	stageController = new Stage(this);

	hitBoxManager = new HitBoxManager();
	hitBoxManager->Init();

	//대문자 주의
	LoadStage("Stage1");
}

void GameScene::Destroy()
{
	Super::Destroy();
}

void GameScene::Update(float deltatTime)
{
	Super::Update(deltatTime);

	hitBoxManager->Update(deltatTime);

	stageController->Update();
}

void GameScene::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void GameScene::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);

	hitBoxManager->DrawHitbox(renderTarget);
}

void GameScene::EraseScene()
{
	Super::EraseScene();

	if (!_gameSceneObjects.empty())
	{
		for (auto gmaeObj : _gameSceneObjects)
		{
			delete gmaeObj;
		}
		_gameSceneObjects.clear();
	}

	

	//컨트롤러 삭제
	for (auto gamdController : _gameControllerMap)
	{
		delete gamdController.first;
	}

	for (auto playerController : _playerControllerVec)
	{
		delete playerController;
	}

	if (stageController != nullptr)
		delete stageController;

	if (hitBoxManager != nullptr)
		delete hitBoxManager;
}



void GameScene::loadResource()
{

}

void GameScene::loadUI()
{
	//TODO
	//HPbar
}

void GameScene::BindController(Controller* controller, LivingObject* ownerObject)
{
	if (_gameControllerMap.find(controller) != _gameControllerMap.end())
		return;

	_gameControllerMap.insert(std::make_pair(controller, ownerObject));
	ownerObject->SetController(controller);
	controller->SetOwner(ownerObject);
}

void GameScene::ChangeControllerOwner(Controller* controller, LivingObject* newownerObject)
{
	LivingObject* PostOwner = controller->GetOwner();

	if (PostOwner == nullptr || _gameControllerMap.find(controller) == _gameControllerMap.end())
		return;

	_gameControllerMap.erase(controller);

	BindController(controller, newownerObject);
}

void GameScene::LoadStage(std::string stage)
{
	if (stageController->LoadStage(stage))
	{
		for (auto& Iter : _gameSceneObjects)
		{
			Iter->Init();
			ReserveAdd(Iter);
		}
	}

	else
	{
		int failed;
	}
}

void GameScene::LoadObject(Object* obj)
{
	_gameSceneObjects.push_back(obj);

	obj->Init();
	ReserveAdd(obj);
}

void GameScene::EraseFromGame(Object* obj)
{
	ReserveRemove(obj);

	auto Iter = _gameSceneObjects.begin();
	while (Iter != _gameSceneObjects.end())
	{
		if (*Iter == obj)
		{
			_gameSceneObjects.erase(Iter);
			break;
		}

		Iter++;
	}

}
