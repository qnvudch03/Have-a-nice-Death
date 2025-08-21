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
	LoadSubWinObject();
}

void EditorScene::Destroy()
{
	ReserveRemove(backGroundObejct);

	for (auto& mainLivingObject : LivingObjects)
	{
		ReserveRemove(mainLivingObject.obj);
	}

	LivingObjects.clear();

	for (auto& mainStaticObject : StaticObjects)
	{
		ReserveRemove(mainStaticObject.obj);
	}

	StaticObjects.clear();



	//자체삭제해야 함
	//SubWinObject
}

void EditorScene::Update(float deltatTime)
{
	Super::Update(deltatTime);

	//서브윈도우 오브젝트 업데이트
	for (auto& livingObj : SubWinObject[0])
	{
		livingObj.obj->Update(deltatTime);
	}
}

void EditorScene::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void EditorScene::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);
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

void EditorScene::RenderSubWin()
{

	D2D1_SIZE_F rtSize = subRenderTarget->GetSize();

	subRenderTarget->BeginDraw();

	subRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	RenderSubWindow();

	HRESULT hr = subRenderTarget->EndDraw();
}

void EditorScene::SetSubWindow(ID2D1RenderTarget* SubRenderTarget, HWND Subhwnd)
{
	if (!IsWindow(Subhwnd))
	{
		int apple = 10;
	}

	if (SubRenderTarget == nullptr || Subhwnd == nullptr)
		return;

	subRenderTarget = SubRenderTarget;
	_subhwnd = Subhwnd;

}

void EditorScene::LoadSubWinObject()
{
	int indexY = 1;
	//캐릭터 Object 부착
	for (auto& characterName : CharacterOjbectList)
	{
		if (characterName.empty())
			break;

		EdiSceneObject character = { characterName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(characterName, "Idle"),
								RenderLayer::Character, Vector(300, indexY*200), ImageAnchor::Bottomcenter)};


		SetCustumAnimSpeed(characterName, character.obj);
		character.obj->collider->DeActivateCollier();
		SubWinObject[0].push_back(character);

		indexY++;
	}

	//스태틱 Object 부착
	{
		indexY = 0;

		std::vector<std::wstring> PlatformNames;

		wchar_t buffer[MAX_PATH];
		DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
		fs::path ResourcePath = fs::path(buffer) / L"../../Resources/Platform/";
		ResourcePath = ResourcePath.lexically_normal();

		for (const auto& entry : fs::directory_iterator(ResourcePath))
		{
			if (entry.is_directory())
			{
				std::string PlatformName = entry.path().filename().string();

				if(PlatformName.find("empty") != std::string::npos || !PlatformName.compare("bannedArea"))
					continue;


				EdiSceneObject platform = { PlatformName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures("Platform", PlatformName),
								RenderLayer::Character, Vector(400, indexY * 200), ImageAnchor::Center) };

				platform.obj->collider->DeActivateCollier();

				SubWinObject[1].push_back(platform);
				indexY++;
			}
		}
	}

}

void EditorScene::RenderSubWindow()
{

	subRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	/*for (auto& SubObjectVec : SubWinObject)
	{
		for (auto& object : SubObjectVec)
		{
			object.obj->Render(subRenderTarget);
		}
	}*/

	SubWinObject[0][0].obj->animator.GetAnimTexture()->Render(subRenderTarget, Vector(50, 50), ImageAnchor::Bottomcenter);
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
				{
					staticObject.obj->custumRenderSizeOrder = true;
					staticObject.obj->custumRenderSize = Vector(1800, 100);

				}	

				else if (!structureName.compare("emptyWall"))
				{
					staticObject.obj->custumRenderSizeOrder = true;
					staticObject.obj->custumRenderSize = Vector(50, 700);
				}

				staticObject.obj->collider->DeActivateCollier();
					
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

void EditorScene::SetCustumAnimSpeed(std::string name, StaticObject* obj)
{
	if (!name.compare("Death"))
	{
		obj->animator.SetAnimSpeed(30);
		return;
	}
	else if (!name.compare("SmallGhost"))
	{
		obj->animator.SetAnimSpeed(10);
		return;
	}
}
