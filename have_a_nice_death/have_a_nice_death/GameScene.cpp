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

	//TODO
	//LoadResoucle�� LoadUI�� �ϰ� ���� ���� �ؽ�Ʈ���� stage ���� �о ������ ���;� ��
	//�о�� �÷��̾� ������Ʈ��, ���� ������Ʈ���� ���⼭ ��Ʈ�ѷ��� ���ε�

	//TODO ���� ���� �� ���� ��, �ϴ� �����̴°� �������ؼ� �̷� �ϴ°���
	//�ӽ��ڵ�
	/*PlayerController* playerController = new PlayerController();
	_playerControllerVec.push_back(playerController);

	static_cast<LivingObject*>(_gameSceneObjects[GameSceneObject::Death])->SetController(playerController);*/


	//�빮�� ����
	LoadStage("Stage1");
}

void GameScene::Destroy()
{
	Super::Destroy();

	if(stageController != nullptr)
		delete stageController;
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

	for (auto playerController : _playerControllerVec)
	{
		delete playerController;
	}
}



void GameScene::loadResource()
{
	_gameSceneObjects.clear();

	//TODO
	//�������� ���� loadResource�� �� ���ΰ�
	//���Ӿ� ������, stageload�� ���ؼ� �Ұ��ΰ�

	auto setGameActor = [this](Object* actor, std::string objectName)
		{
			_gameSceneObjects[objectName] = actor;
			actor->animator.SetAnimSpeed(DefaultAnimSpeed);
		};

	//���ҽ� �Ŵ�������, �ʿ��� Texture���� �������� (��� ȭ��, ĳ����, ���۹�ư, ������ ��ư)
	// TODO
	//���⼭ �� �� ��������, LoadStage���� �׶� addreserve ����
	//_gameSceneObjects[GameSceneObject::Death] = new Death(SpriteManager::GetInstance()->GetTextureMap("Death"), RenderLayer::Character, ImageAnchor::Bottomcenter);

	//�ӽ� �ڵ�
	{

	}


	for (auto& obj : _gameSceneObjects)
	{
		ReserveAdd(obj.second);
	}
}

void GameScene::loadUI()
{
	//TODO
	//HPbar
}

void GameScene::BindController(Controller* controller, LivingObject* ownerObject)
{
	if (_gameControllerMap.find(controller) == _gameControllerMap.end())
		return;

	_gameControllerMap.insert(std::make_pair(controller, ownerObject));
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
		int succed;
	}

	else
	{
		int failed;
	}
}
