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
#include "UIManager.h"
#include "UIButton.h"
#include "UI.h"
#include "TimeManager.h"
#include "EffectManager.h"

#include <random>

void GameScene::Init()
{
	Super::Init();

	hitBoxManager = new HitBoxManager();
	hitBoxManager->Init();

	//effectManager = new EffectManager();

	MappingInGameFunction();

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

	if (effectManager != nullptr)
	{
		effectManager->EraseEffects();
		delete effectManager;
	}
}



void GameScene::loadResource()
{

}

void GameScene::loadUI()
{
	SceneUI = UIManager::GetInstance()->GetSceneUI(this);
}

void GameScene::MappingInGameFunction()
{
	_inGameActionMap.clear();

	_inGameActionMap = {
		{"BTN_CURSE_ACTIONSPEED",		[this]() { Curse_ActionSpeed(); }},
		{"BTN_CURSE_ATK",				[this]() { Curse_Attack(); }},
		{"BTN_CURSE_DASHCOOLTIME",		[this]() { Curse_DashCoolTime(); }},
		{"BTN_CURSE_DEF",				[this]() { Curse_Deffense(); }},
		{"BTN_CURSE_HEALING",			[this]() { Curse_Healing(); }}

	};

	BindingWithBtn();

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
	if (stageController != nullptr)
		delete stageController;

	stageController = new Stage(this);

	if (stageController->LoadStage(stage))
	{
		for (auto& Iter : _gameSceneObjects)
		{
			Iter->Init();
			ReserveAdd(Iter);
		}

		stage_count++;
	}

	else
	{
		int failed;
	}

	if (stage.compare("Stage1"))
	{
		stageController->SetPlayerData(playerSaveParam);
		stageController->UpdateHPBar();
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

std::string GameScene::GetNextStage()
{
	if (stage_count == 0)			return "Stage1";
	else if (stage_count == 1)		return "Stage2";
	else if (stage_count == 2)		return "Stage3";
}

void GameScene::SetUI_PlayGame()
{
	StartObjectUpdate();

	GetUIByName("HPbar")->SetOpen(true);
	GetUIByName("HPbar_body")->SetOpen(true);

	GetUIByName("ARewordBackGround")->SetOpen(false);

	for (auto& button : Curse_List)
	{
		button->SetOpen(false);
	}

}

void GameScene::SetUI_SelectReword()
{
	StopObjectUpdate();

	GetUIByName("HPbar")->SetOpen(false);
	GetUIByName("HPbar_body")->SetOpen(false);

	GetUIByName("ARewordBackGround")->SetOpen(true);

	std::random_device rd;
	std::vector< UIButton*> Curses = Curse_List;


	//Select Curse
	for (int i = 0; i < 3; i++)
	{
		auto iter = Curses.begin();

		int randomCurseIndex = rd() % Curses.size();
		auto& selectedCurse = (*(iter + randomCurseIndex));
		selectedCurse->SetOpen(true);
		selectedCurse->SetTargetpos(Vector(200 + 500 * i, 50));
		selectedCurse->SetCurrentpos(Vector(200 + 500 * i, 800));
		selectedCurse->SetMoveDirection(Vector(0, -1));
		Curses.erase(iter + randomCurseIndex);
	}
}

void GameScene::SavePlayData()
{

	stageController->ApplyPlayerData(playerSaveParam);
}

void GameScene::GoNextStage()
{
	LoadStage(GetNextStage());
}

void GameScene::BindingWithBtn()
{
	Curse_List.clear();

	for (auto& btn : *SceneUI)
	{
		if (btn->_name.find("BTN_CURSE") == std::string::npos)
			continue;

		UIButton* buttonCurse = static_cast<UIButton*>(btn);

		buttonCurse->_actionFunc = _inGameActionMap[btn->_name];
		Curse_List.push_back(buttonCurse);
	}
}

void GameScene::Curse_Attack()
{
	LivingObject* player = stageController->GetPlayer();
	if (player == nullptr)
		return;

	player->AddStatByIndex(3, 5);

	//0.5초 게임 재 시작
	TimeManager::GetInstance()->AddTimer(Timer([this]() {SetUI_PlayGame(); }, 0.5));
}

void GameScene::Curse_ActionSpeed()
{
	LivingObject* player = stageController->GetPlayer();
	if (player == nullptr)
		return;

	player->actionSpeed *= 1.2;

	TimeManager::GetInstance()->AddTimer(Timer([this]() {SetUI_PlayGame(); }, 0.5));
}

void GameScene::Curse_DashCoolTime()
{
	Death* player = dynamic_cast<Death*>(stageController->GetPlayer());
	if (player == nullptr)
		return;

	player->FixDashCollTImeByRatio(0.8);

	TimeManager::GetInstance()->AddTimer(Timer([this]() {SetUI_PlayGame(); }, 0.5));
}

void GameScene::Curse_Deffense()
{
	LivingObject* player = stageController->GetPlayer();
	if (player == nullptr)
		return;

	player->AddStatByIndex(4, 2);

	TimeManager::GetInstance()->AddTimer(Timer([this]() {SetUI_PlayGame(); }, 0.5));
}

void GameScene::Curse_Healing()
{
	LivingObject* player = stageController->GetPlayer();
	if (player == nullptr)
		return;

	player->AddStatByIndex(1, 30);
	stageController->UpdateHPBar();

	TimeManager::GetInstance()->AddTimer(Timer([this]() {SetUI_PlayGame(); }, 0.5));
}
