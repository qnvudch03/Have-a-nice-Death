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

#include "json.hpp"

using json = nlohmann::json;

Stage::~Stage()
{
}

bool Stage::LoadStage(std::string stage)
{
	if (!stageObjectVec.empty())
	{
		for (auto Iter : stageObjectVec)
		{
			delete Iter;
		}
	}


	if (LoadStageInfo(stage) == false)
		return false;

	return true;
}

bool Stage::LoadStageInfo(std::string stage)
{
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

	auto setStageObject = [this](Object* actor, Vector pos)
		{
			stageObjectVec.push_back(actor);
			actor->SetPos(pos);
		};

	//오브젝트 종류에 맞게 Vec에 넣기
	{
		//배경화면 셋팅
		std::string background = stageData["BackGround"];

		stageObjectVec.push_back(new StaticObject(SpriteManager::GetInstance()->GetTextures("StageBackground", stage), 
													RenderLayer::Background, Vector(0, 0), ImageAnchor::Topleft));

		//LivingObject 셋팅
		auto livingObjects = stageData["LivingObjects"]["Object"];
		for (const auto& object : livingObjects)
		{
			std::string owner = object["owner"];
			std::string type = object["type"];
			Vector position = Vector(object["position"][0] , object["position"][1]);

			if (!owner.compare("Player"))
			{
				//플레이어가 몬스터 일 수도 있으니 일단은 libingobject로 하자
				LivingObject* livingObject = new Death(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
																ImageAnchor::Bottomcenter);
				setStageObject(livingObject, position);

				livingObject->SetState("Idle");

				//컨트롤러 바인딩
				PlayerController* playerController = new PlayerController();
				//livingObject->SetController(playerController);
				gameScene->BindController(playerController, livingObject);
			}

			else if (!owner.compare("AI"))
			{
				//플레이어가 몬스터 일 수도 있으니 일단은 libingobject로 하자
				LivingObject* livingObject = new LivingObject(SpriteManager::GetInstance()->GetTextureMap(type), RenderLayer::Character,
					ImageAnchor::Bottomcenter);
				setStageObject(livingObject, position);

				livingObject->SetState("Idle");

				//컨트롤러 바인딩
				AIController* aiController = new AIController();
				//livingObject->SetController(aiController);
				gameScene->BindController(aiController, livingObject);
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

			setStageObject(staticObject, position);
		}


		for (auto& Iter : stageObjectVec)
		{
			gameScene->GetGameSceneObjectVec()->push_back(Iter);
		}

	}
	



	return true;
}
