#include "pch.h"
#include "EditorScene.h"
#include "StaticObject.h"
#include "SpriteManager.h"
#include "Game.h"
#include "InputManager.h"

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

	subRenderTarget->Clear(D2D1::ColorF(currentColor));
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
	int OffsetY = 0;
	//캐릭터 Object 부착
	for (auto& characterName : CharacterOjbectList)
	{
		if (characterName.empty())
			break;

		EdiSceneObject character = { "Player",characterName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(characterName, "Idle"),
								RenderLayer::Character, Vector(0, 0), ImageAnchor::Center) };


		Vector textureSize = character.obj->animator.GetAnimTexture()->GetTextureSize();

		character.obj->SetPos(Vector(100, OffsetY + textureSize.y / 2));
		character.obj->collider->DeActivateCollier();
		character.obj->animator.StopAnim();
		SetCustumAnimSpeed(characterName, character.obj);


		
		SubWinObject[0].push_back(character);

		OffsetY += (textureSize.y) + 20;
	}

	if (WinOffsetYMax < OffsetY)
		WinOffsetYMax = OffsetY;

	//스태틱 Object 부착
	{
		OffsetY = 0;

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

				if (PlatformName.find("empty") != std::string::npos || !PlatformName.compare("bannedArea"))
					continue;


				EdiSceneObject platform = { "Platform", PlatformName,
				new StaticObject(SpriteManager::GetInstance()->GetTextures("Platform", PlatformName),
								RenderLayer::Character, Vector(0, 0), ImageAnchor::Center) };


				Vector textureSize = platform.obj->animator.GetAnimTexture()->GetTextureSize();
				platform.obj->SetPos(Vector(400, OffsetY + textureSize.y / 2));

				platform.obj->collider->DeActivateCollier();

				SubWinObject[1].push_back(platform);

				OffsetY += (textureSize.y) + 50;
			}
		}
	}

	if (WinOffsetYMax < OffsetY)
		WinOffsetYMax = OffsetY;

}

void EditorScene::RenderSubWindow()
{
	for (auto& SubObjectVec : SubWinObject)
	{
		for (auto& object : SubObjectVec)
		{
			object.obj->RenderWithWinOffset(subRenderTarget, subWinOffset);
		}
	}
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

			EdiSceneObject character = { "Player", name,
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
				staticObject = { "Platform", structureName,
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
				staticObject = { "Platform", structureName,
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

void EditorScene::AddWinOffset(Vector amount)
{

	if (amount.y > 0 && subWinOffset.y == 0)
		return;

	if (amount.y < 0 && subWinOffset.y >= WinOffsetYMax)
	{
		subWinOffset.y = WinOffsetYMax;
		return;
	}

	subWinOffset.x += amount.x;
	subWinOffset.y += amount.y;


}

std::pair<std::string, std::string> EditorScene::GetSellectedEdiSceneObjectData()
{
	Vector mousePos = subWinMouseClickedPos;

	mousePos.x -= subWinOffset.x;
	mousePos.y -= subWinOffset.y;

	std::pair<std::string, std::string> SendData;

	for (auto& Objects : SubWinObject)
	{
		for (auto& Obj : Objects)
		{
			Vector ObjectPos = Obj.obj->GetPos();
			Vector TextureSize = Obj.obj->animator.GetAnimTexture()->GetTextureSize();

			float halfX = TextureSize.x * 0.5;
			float halfY = TextureSize.y * 0.5;

			if (mousePos.x > ObjectPos.x - halfX &&
				mousePos.y > ObjectPos.y - halfY &&
				mousePos.x < ObjectPos.x + halfX &&
				mousePos.y < ObjectPos.y + halfY)

			{
				SendData = std::make_pair(Obj.type, Obj.name);
				Obj.obj->animator.StartAnim();
				StopAllSubWinObjAnimExcep(&Obj);
			}
		}
	}

	return SendData;
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
	else if (!name.compare("MedGhost"))
	{
		obj->animator.SetAnimSpeed(10);
		return;
	}
}

void EditorScene::StopAllSubWinObjAnimExcep(EdiSceneObject* theExcep)
{
	for (auto& Obj : SubWinObject[0])
	{
		if(Obj.obj != theExcep->obj)
		Obj.obj->animator.StopAnim();
	}
}

void EditorScene::ChangeColor(bool num)
{

	auto CompareColor = [](const D2D1::ColorF& c1, const D2D1::ColorF& c2) -> bool
		{
			const float EPSILON = 0.001f;
			return fabs(c1.r - c2.r) < EPSILON &&
				fabs(c1.g - c2.g) < EPSILON &&
				fabs(c1.b - c2.b) < EPSILON &&
				fabs(c1.a - c2.a) < EPSILON;
		};


	if (num == true)
	{
		//if(currentColor == D2D1::ColorF::Coral)
		if (CompareColor(currentColor, D2D1::ColorF::Coral))
		{
			return;
		}

		else
		{
			currentColor = D2D1::ColorF::Coral;
		}
	}

	else if (num == false)
	{
		if (CompareColor(currentColor, D2D1::ColorF::Aqua))
		{
			return;
		}

		else
		{
			currentColor = D2D1::ColorF::Aqua;
		}
	}

	//현재 에디터 캐릭터의 정보를 수정한다.

	std::string characterType;

	if (CompareColor(currentColor, D2D1::ColorF::Coral))
	{
		characterType = "Player";
	}

	else
	{
		characterType = "AI";
	}

	for (auto& Obj : SubWinObject[0])
	{
		Obj.type = characterType;
	}
}
