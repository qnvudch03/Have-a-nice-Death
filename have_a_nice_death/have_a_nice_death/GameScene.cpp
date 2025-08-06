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
	//LoadResoucle랑 LoadUI랑 하고 게임 씬은 텍스트에서 stage 파일 읽어서 정보를 얻어와야 해
	//읽어온 플레이어 오브젝트와, 몬스터 오브젝트들을 여기서 컨트롤러에 바인딩

	//TODO 여기 구조 손 봐야 함, 일단 움직이는거 보이위해서 이래 하는거임
	//임시코드
	/*PlayerController* playerController = new PlayerController();
	_playerControllerVec.push_back(playerController);

	static_cast<LivingObject*>(_gameSceneObjects[GameSceneObject::Death])->SetController(playerController);*/


	//대문자 주의
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

	//컨트롤러 삭제
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
	//스테이지 별로 loadResource를 할 것인가
	//게임씬 내에서, stageload를 통해서 할것인가

	auto setGameActor = [this](Object* actor, std::string objectName)
		{
			_gameSceneObjects[objectName] = actor;
			actor->animator.SetAnimSpeed(DefaultAnimSpeed);
		};

	//리소스 매니저에서, 필요한 Texture들을 가져오기 (배경 화면, 캐릭터, 시작버튼, 에디터 버튼)
	// TODO
	//여기서 싹 다 가져오고, LoadStage에서 그때 addreserve 하자
	//_gameSceneObjects[GameSceneObject::Death] = new Death(SpriteManager::GetInstance()->GetTextureMap("Death"), RenderLayer::Character, ImageAnchor::Bottomcenter);

	//임시 코드
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
