#include "pch.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "LivingObject.h"
#include "SpriteManager.h"
#include "Death.h"
#include "Controller.h"
#include "PlayerController.h"

void GameScene::Init()
{
	Super::Init();

	stageController = new Stage(this);

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
