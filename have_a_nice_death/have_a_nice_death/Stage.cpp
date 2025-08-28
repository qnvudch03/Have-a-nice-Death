#include "pch.h"
#include "Stage.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "SpriteManager.h"
#include "LivingObject.h"
#include "PlayerController.h"
#include "AIController.h"
#include "AIBossController.h"
#include "UIManager.h"
#include "UI.h"
#include "InteractableElevator.h"
#include "ExcapeDoor.h"

#include "Contractor.h"
#include "Death.h"
#include "SmallGhost.h"
#include "W7.h"
#include "MedChost.h"
#include "Pill.h"
#include "Nurse.h"

#include <random>

#include "json.hpp"

using json = nlohmann::json;

Stage::~Stage()
{
	hpBar = nullptr;

	for (auto& preloadObject : stagePreloadObjectVec)
	{
		gameScene->EraseFromGame(preloadObject);
	}
}

bool Stage::LoadStage(std::string stage)
{
	stageLivingObjectVec.clear();
	stageStaticObjectVec.clear();

	currentStage = stage;

	if (LoadStageInfo(stage) == false)
		return false;



	hpBar = gameScene->GetUIByName("HPbar_body");

	UpdateHPBar();


	gameScene->SetUI_PlayGame();

	if (!currentStage.compare("Stage5"))
	{
		gameScene->SetUI_EndingScene();
		gameClearDoor = new ExcapeDoor(RenderLayer::InterActObject, ImageAnchor::Bottomcenter, { GWinSizeX * 0.5, GWinSizeY - 80 });

		gameScene->LoadObject(gameClearDoor);
	}

	return true;
}

void Stage::Update()
{
	if (bIsStageReady)
		return;

	if (player->GetPos().x >= 300)
	{
		bIsStageReady = true;
		StartStage();
	}
}

void Stage::UpdateHPBar()
{
	float currentHP = player->GetStat().hp;
	float maxHP = player->GetStat().maxhp;

	currentHP = (currentHP <= 0) ? 0 : currentHP;

	hpBar->SetRatioX(currentHP / maxHP);
}

bool Stage::LoadStageInfo(std::string stage)
{
	TotalEnemy = 0;
	MonsterCounter = 0;
	WaveMonstercount.clear();

	std::string Filename = stage + ".stage";
	wchar_t buffer[MAX_PATH];
	DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
	fs::path ResourcePath = fs::path(buffer) / L"../../StageInfo/";
	ResourcePath = ResourcePath.lexically_normal();

	fs::path fullFilePath = ResourcePath / fs::path(Filename);

	std::ifstream file(fullFilePath);
	if (!file.is_open())
	{
		return false;
	}

	json stageData;
	file >> stageData;

	auto setStageObject = [this](Object* actor, Vector pos, int type)
		{

			if (type == 0)
			{
				//Preload object
				stagePreloadObjectVec.push_back(actor);
				actor->SetPos(pos);
			}

			else if (type == 1)
			{
				//static object
				stageStaticObjectVec.push_back(actor);
				actor->SetPos(pos);
			}

			else if (type == 2)
			{
				//living object
				stageLivingObjectVec.push_back(actor);
				actor->SetPos(pos);
			}
		};

	//오브젝트 종류에 맞게 Vec에 넣기
	{
		//배경화면 셋팅
		std::string background = stageData["BackGround"];

		stagePreloadObjectVec.push_back(new StaticObject(SpriteManager::GetInstance()->GetTextures("StageBackground", stage),
			RenderLayer::Background, Vector(0, 0), ImageAnchor::Topleft));

		//LivingObject 셋팅
		auto livingObjects = stageData["LivingObjects"]["Object"];
		for (const auto& object : livingObjects)
		{
			std::string owner = object["owner"];
			std::string type = object["type"];
			Vector position = Vector(object["position"][0], object["position"][1]);

			if (!owner.compare("Player"))
			{
				LivingObject* livingObject = MakeCharacter(type, position);

				if (livingObject == nullptr)
					continue;

				setStageObject(livingObject, position, 0);

				//컨트롤러 바인딩
				PlayerController* playerController = new PlayerController();
				gameScene->BindController(playerController, livingObject);

				livingObject->OnDie = [this](LivingObject* livingObject) {this->playerDie(livingObject); };
				livingObject->OnHitted = [this]() {this->playerHitted(); };

				//TODO
				// 책도 나중에 붙여보자
				//livingObject->SetBook(new Book(livingObject));

				player = livingObject;

			}

			else if (!owner.compare("AI"))
			{
				//플레이어가 몬스터 일 수도 있으니 일단은 libingobject로 하자
				LivingObject* livingObject = MakeCharacter(type, position);

				if (livingObject == nullptr)
					continue;

				setStageObject(livingObject, position, 2);


				//컨트롤러 바인딩
				if (type.find("Boss") == std::string::npos)
				{
					AIController* aiController = new AIController();
					gameScene->BindController(aiController, livingObject);
				}
				

				else
				{
					AIBossController* bossController  = new AIBossController();
					gameScene->BindController(bossController, livingObject);
				}

				livingObject->OnDie = [this](LivingObject* livingObject) {this->enemyDie(livingObject); };

				TotalEnemy++;
			}


		}

		auto staticObjects = stageData["StaticObjects"]["Object"];
		for (const auto& object : staticObjects)
		{
			std::string type = object["type"];
			std::string structureName = object["name"];
			Vector position = Vector(object["position"][0], object["position"][1]);

			StaticObject* staticObject = new StaticObject(SpriteManager::GetInstance()->GetTextures(type, structureName),
				RenderLayer::Platform, position, ImageAnchor::Center);

			if (!structureName.compare("emptyground") ||
				!structureName.compare("emptyWall"))
			{
				setStageObject(staticObject, position, 0);
			}

			else
			{
				setStageObject(staticObject, position, 1);
			}

		}

		WaveMonstercount = divideIntoThree(TotalEnemy);

		//플레이어와 바탕화면은 미리 어차피 로딩
		for (auto& Iter : stagePreloadObjectVec)
		{
			gameScene->GetGameSceneObjectVec()->push_back(Iter);
		}
	}

	return true;
}

void Stage::ApplyPlayerData(std::map<std::string, float>& playerSaveParam)
{
	if (player == nullptr)
		return;

	Death* death = static_cast<Death*>(player);

	playerSaveParam["currentHP"] = player->GetStat().hp;
	playerSaveParam["defBonus"] = player->GetStat().def;
	playerSaveParam["atkBonus"] = player->GetStat().atk;
	playerSaveParam["actionSpeed"] = player->actionSpeed;

	if (death != nullptr)
	{
		playerSaveParam["dashCollTime"] = death->GetDashCollTime();
	}

}

void Stage::SetPlayerData(std::map<std::string, float>& playerSaveParam)
{
	Death* death = static_cast<Death*>(player);

	player->SetStatByIndex(1, playerSaveParam["currentHP"]);
	player->SetStatByIndex(3, playerSaveParam["atkBonus"]);
	player->SetStatByIndex(4, playerSaveParam["defBonus"]);
	player->actionSpeed = playerSaveParam["actionSpeed"];

	if (death != nullptr)
	{
		death->SetDashCollTime(playerSaveParam["dashCollTime"]);
	}
}

LivingObject* Stage::GetEnemy()
{
	for (auto Obj : currentWaveEnemy)
	{
		if (Obj == nullptr)
			continue;

		LivingObject* livingObj = static_cast<LivingObject*>(Obj);
		if (livingObj->IsActive)
			return livingObj;
	}
	return nullptr;
}

std::vector<int> Stage::divideIntoThree(int totalEnemy)
{
	int part1 = totalEnemy / 3;
	int part2 = (totalEnemy - part1) / 2;
	int part3 = totalEnemy - part1 - part2;

	return { part1, part2, part3 };
}

LivingObject* Stage::MakeCharacter(std::string type, Vector pos)
{
	LivingObject* livingObject = nullptr;

	if (!type.compare("Death"))
	{
		livingObject = new Death(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);

		//livingObject = death;
	}

	else if (!type.compare("SmallGhost"))
	{
		livingObject = new SmallGhost(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}

	else if (!type.compare("Boss_W7"))
	{
		livingObject = new W7(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}

	else if (!type.compare("MedGhost"))
	{
		livingObject = new MedChost(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}

	else if (!type.compare("Pill"))
	{
		livingObject = new Pill(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}

	else if (!type.compare("Nurse"))
	{
		livingObject = new Nurse(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}

	return livingObject;
}

//void Stage::SetReady(Object* obj)
//{
//	obj->animator.SetAnimSpeed(0);
//	obj->animator.SetAnimLoop(false);
//	obj->animator.StopAnim();
//	obj->collider->DeActivateCollier();
//}

void Stage::playerDie(LivingObject* player)
{
	//플레이어 사망시 처리할 부분
	gameScene->SetUI_GameOver();
}

void Stage::playerHitted()
{
	UpdateHPBar();
}

void Stage::enemyDie(LivingObject* deathCharacater)
{
	//적 사망시 처리해야 할 부분
	MonsterCounter--;

	currentWaveEnemy.erase(deathCharacater);

	if (MonsterCounter < 0)
	{
		int apple = 10;
		return;
	}

	if (MonsterCounter == 0)
	{
		WaveCount++;
		StartWave();
	}

	//최소 1마리 이상은 몬스터가 있다는 전제에 코드
	if (WaveCount == -1)
	{
		StageClear();
	}

}

void Stage::StartStage()
{
	if (!currentStage.compare("Stage5"))
		return;

	//벽과 오브젝트 화면에 로딩
	for (auto& Iter : stageStaticObjectVec)
	{
		gameScene->LoadObject(Iter);

		Iter->animator.StartAnim();
		Iter->animator.SetAnimSpeed(20);
		Iter->animator.SetAnimLoop(false);
	}

	StartWave();

	if (WaveCount <= -1)
	{
		StageClear();
	}
}

void Stage::StartWave()
{
	int EnemyNum = 0;
	MonsterCounter = 0;

	while (EnemyNum == 0)
	{
		if (WaveCount > 2)
			break;

		EnemyNum = WaveMonstercount[WaveCount];

		if (EnemyNum != 0)
			break;

		else if (EnemyNum == 0)
			WaveCount++;
	}

	if (WaveCount > 2)
		WaveCount = -1;

	MonsterCounter = EnemyNum;

	for (int i = 0; i < EnemyNum; i++)
	{
		std::random_device rd;

		int randomIndex = (rd() % stageLivingObjectVec.size());

		gameScene->LoadObject(stageLivingObjectVec[randomIndex]);
		currentWaveEnemy.insert(stageLivingObjectVec[randomIndex]);
		stageLivingObjectVec.erase(stageLivingObjectVec.begin() + randomIndex);
	}
}

void Stage::StageClear()
{
	//static Object들 제거
	{
		for (auto& Iter : stageStaticObjectVec)
		{
			auto& Animator = Iter->animator;

			if (Animator.TextureNum == 1)
			{
				gameScene->EraseFromGame(Iter);
			}

			else
			{
				Animator.SetReversePlay();
				Animator.StartAnim();
				Animator.onAnimEnd = [this, Iter]() {gameScene->EraseFromGame(Iter); };
			}
		}
	}

	//탈출용 엘레베이터 소환
	{
		Vector elevatorPosition = Vector(GWinSizeX - 200, GWinSizeY - 120);

		excapeElevator = new InteractableElevator(RenderLayer::InterActObject, ImageAnchor::Bottomcenter, elevatorPosition);
		excapeElevator->animator.SetAnimSpeed(20);
		gameScene->LoadObject(excapeElevator);
	}

	//오샤 소환
	{
		Vector ContractorPosition = Vector(GWinSizeX * 0.5, GWinSizeY - 100);

		contractor = new Contractor(RenderLayer::InterActObject, ImageAnchor::Bottomcenter, ContractorPosition);
		contractor->animator.SetAnimSpeed(15);
		gameScene->LoadObject(contractor);

	}
}
