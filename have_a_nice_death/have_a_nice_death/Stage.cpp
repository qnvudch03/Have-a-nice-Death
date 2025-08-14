#include "pch.h"
#include "Stage.h"
#include "GameScene.h"
#include "Object.h"
#include "StaticObject.h"
#include "SpriteManager.h"
#include "LivingObject.h"
#include "Death.h"
#include "PlayerController.h"
#include "AIController.h"
#include "SmallGhost.h"
#include "Elevator.h"

#include <random>

#include "json.hpp"

using json = nlohmann::json;

Stage::~Stage()
{
}

bool Stage::LoadStage(std::string stage)
{
	/*if (!stageObjectVec.empty())
	{
		for (auto Iter : stageObjectVec)
		{
			delete Iter;
		}
	}*/

	if (!stageLivingObjectVec.empty())
	{
		for (auto Iter : stageLivingObjectVec)
		{
			delete Iter;
		}
	}

	if (!stageStaticObjectVec.empty())
	{
		for (auto Iter : stageStaticObjectVec)
		{
			delete Iter;
		}
	}


	if (LoadStageInfo(stage) == false)
		return false;

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

	//������Ʈ ������ �°� Vec�� �ֱ�
	{
		//���ȭ�� ����
		std::string background = stageData["BackGround"];

		stagePreloadObjectVec.push_back(new StaticObject(SpriteManager::GetInstance()->GetTextures("StageBackground", stage),
			RenderLayer::Background, Vector(0, 0), ImageAnchor::Topleft));

		//LivingObject ����
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

				//��Ʈ�ѷ� ���ε�
				PlayerController* playerController = new PlayerController();
				//livingObject->SetController(playerController);
				gameScene->BindController(playerController, livingObject);

				//TODO
				// å�� ���߿� �ٿ�����
				//livingObject->SetBook(new Book(livingObject));

				player = livingObject;
			}

			else if (!owner.compare("AI"))
			{
				//�÷��̾ ���� �� ���� ������ �ϴ��� libingobject�� ����
				LivingObject* livingObject = MakeCharacter(type, position);

				if (livingObject == nullptr)
					continue;

				setStageObject(livingObject, position, 2);


				//��Ʈ�ѷ� ���ε�
				AIController* aiController = new AIController();
				//livingObject->SetController(aiController);
				gameScene->BindController(aiController, livingObject);

				//SetReady(livingObject);

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

		//�÷��̾�� ����ȭ���� �̸� ������ �ε�
		for (auto& Iter : stagePreloadObjectVec)
		{
			gameScene->GetGameSceneObjectVec()->push_back(Iter);
		}
	}

	return true;
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
		Death* death = new Death(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);

		Vector elevatorPosition = pos;
		elevatorPosition.x -= 20;
		elevatorPosition.y += 10;

		Elevator* elevator = new Elevator(SpriteManager::GetInstance()->GetTextures("Elevator", "open"), RenderLayer::Platform, elevatorPosition, ImageAnchor::Bottomcenter);

		elevator->animator.onAnimEnd = [this, death, elevator]() {

			elevator->callCount++;

			if (elevator->callCount == 1)
			{
				death->OnDeathSpawn();
				elevator->SetAnimaotrTextures(SpriteManager::GetInstance()->GetTextures("Elevator", "close"), false);
			}

			else if (elevator->callCount == 2)
			{
				gameScene->EraseFromGame(elevator);
			}

			};

		livingObject = death;

		gameScene->GetGameSceneObjectVec()->push_back(elevator);
	}

	else if (!type.compare("SmallGhost"))
	{
		livingObject = new SmallGhost(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
			ImageAnchor::Bottomcenter);
	}
	return livingObject;
}

void Stage::SetReady(Object* obj)
{
	obj->animator.SetAnimSpeed(0);
	obj->animator.SetAnimLoop(false);
	obj->animator.StopAnim();
	obj->collider->DeActivateCollier();
}

void Stage::StartStage()
{
	//���� ������Ʈ ȭ�鿡 �ε�
	for (auto& Iter : stageStaticObjectVec)
	{
		gameScene->LoadObject(Iter);

		Iter->animator.StartAnim();
		Iter->animator.SetAnimSpeed(20);
		Iter->animator.SetAnimLoop(false);
	}

	StartWave();
}

void Stage::StartWave()
{
	int EnemyNum = 0;

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


	for (int i = 0; i < EnemyNum; i++)
	{
		std::random_device rd;

		int randomIndex = (rd() % stageLivingObjectVec.size());

		gameScene->LoadObject(stageLivingObjectVec[randomIndex]);

		stageLivingObjectVec.erase(stageLivingObjectVec.begin() + randomIndex);
	}
}
