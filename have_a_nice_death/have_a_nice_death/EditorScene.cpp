#include "pch.h"
#include "EditorScene.h"
#include "StaticObject.h"
#include "SpriteManager.h"

#include "json.hpp"

using json = nlohmann::json;

void EditorScene::Init()
{
	if (subRenderTarget == nullptr || _subhwnd == nullptr)
		return;

	ShowWindow(_subhwnd, SW_SHOW);
	UpdateWindow(_subhwnd);

	currentStage = "Stage1";

	ReadStageData(currentStage);
}

void EditorScene::Destroy()
{
}

void EditorScene::Update(float deltatTime)
{
	Super::Update(deltatTime);
	/*for (auto& LivingObj : LivingObjects)
	{
		if (LivingObj.obj == nullptr)
			continue;

		LivingObj.obj->Update(deltatTime);
	}*/
}

void EditorScene::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void EditorScene::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);

	RdnerSubWindow();

}

void EditorScene::EraseScene()
{
	for (auto& livingObject : LivingObjects)
	{
		delete livingObject.obj;
	}

	LivingObjects.clear();

	for (auto& staticObject : StaticObjects)
	{
		delete staticObject.obj;
	}

	StaticObjects.clear();
}

void EditorScene::SetSubWindow(ID2D1RenderTarget* SubRenderTarget, HWND Subhwnd)
{
	if (SubRenderTarget == nullptr || Subhwnd == nullptr)
		return;

	subRenderTarget = SubRenderTarget;
	_subhwnd = Subhwnd;

}

void EditorScene::RdnerSubWindow()
{
	//subRenderTarget->BeginDraw();

	//subRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	////ToDo

	//subRenderTarget->EndDraw();
}

bool EditorScene::ReadStageData(std::string stageName)
{

	LivingObjects.clear();
	StaticObjects.clear();

	if (LoadJsonFile(stageName) == false)
		return false;


	return true;
}

bool EditorScene::LoadJsonFile(std::string FileName)
{
	auto SetCustumAnimSpeed = [this](std::string name, StaticObject* obj)
		{
			if (!name.compare("Death"))
			{
				obj->animator.SetAnimSpeed(30);
				//return;
			}		
			else if (!name.compare("SmallGhost"))
			{
				obj->animator.SetAnimSpeed(10);
				//return;
			}
		};



	std::string Filename = FileName + ".stage";
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

	backGroundObejct = new StaticObject(SpriteManager::GetInstance()->GetTextures("StageBackground", FileName),
		RenderLayer::Background, Vector(0, 0), ImageAnchor::Topleft);

	if (backGroundObejct != nullptr)
		ReserveAdd(backGroundObejct);

	{
		auto livingObjects = stageData["LivingObjects"]["Object"];
		for (const auto& object : livingObjects)
		{
			std::string name = object["type"];
			Vector position = Vector(object["position"][0], object["position"][1]);

			EdiSceneObject character = { name,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(name, "Idle"),
								RenderLayer::Character, position, ImageAnchor::Bottomcenter) };


			SetCustumAnimSpeed(name, character.obj);
			LivingObjects.push_back(character);
		}
	}
	

	{
		auto staticObjects = stageData["StaticObjects"]["Object"];
		for (const auto& object : staticObjects)
		{
			std::string type = object["type"];
			std::string structureName = object["name"];
			Vector position = Vector(object["position"][0], object["position"][1]);

			if (!type.compare("Wall"))
				continue;

			EdiSceneObject staticObject;

			if (structureName.find("empty") != std::string::npos)
			{
				staticObject = { structureName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(type, "bannedArea"),
								RenderLayer::Platform, position, ImageAnchor::Center) };

				if (!structureName.compare("emptyground"))
					staticObject.obj->animator.GetAnimTexture()->ReSizeTexture(Vector(1800, 100));

				if (!structureName.compare("emptyWall"))
					staticObject.obj->animator.GetAnimTexture()->ReSizeTexture(Vector(50, 350));
			}

			else
			{
				staticObject = { structureName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(type, structureName),
								RenderLayer::Platform, position, ImageAnchor::Center) };
			}

			StaticObjects.push_back(staticObject);
		}
	}

	for (auto& LivingObj : LivingObjects)
	{
		if (LivingObj.obj == nullptr)
			continue;

		ReserveAdd(LivingObj.obj);
	}

	for (auto& StaticObj : StaticObjects)
	{
		if (StaticObj.obj == nullptr)
			continue;

		ReserveAdd(StaticObj.obj);
	}

	return false;
}
