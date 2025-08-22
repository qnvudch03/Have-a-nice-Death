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

	//화면에 있는 프리뷰 오브젝트 업데이트
	if (RecievedPreiVewObjectContainer.second != nullptr &&
		!RecievedPreiVewObjectContainer.first.first.empty())
	{
		RecievedPreiVewObjectContainer.second->SetPos(InputManager::GetInstance()->GetMousePos());
		RecievedPreiVewObjectContainer.second->Update(deltatTime);
	}
}

void EditorScene::PostUpdate(float deltaTime)
{
	Super::PostUpdate(deltaTime);
}

void EditorScene::Render(ID2D1RenderTarget* renderTarget)
{
	Super::Render(renderTarget);

	//프리뷰 오브젝트 렌더
	if (RecievedPreiVewObjectContainer.second != nullptr ||
		!RecievedPreiVewObjectContainer.first.first.empty())
	{
		RecievedPreiVewObjectContainer.second->RenderWithOpacity(renderTarget, 0.7);
	}
}

void EditorScene::EraseScene()
{

	if (!WriteStageData())
	{
		//FileSave Faild
		throw std::runtime_error("파일 저장 실패: " + currentStage);
	}

	for (auto& livingObject : LivingObjects)
	{
		//delete livingObject.obj;
		ReserveRemove(livingObject.obj);
	}

	LivingObjects.clear();

	for (auto& staticObject : StaticObjects)
	{
		//delete staticObject.obj;
		ReserveRemove(staticObject.obj);
	}

	StaticObjects.clear();

	if (RecievedPreiVewObjectContainer.second != nullptr)
	{
		delete RecievedPreiVewObjectContainer.second;
		RecievedPreiVewObjectContainer.second = nullptr;
	}

	if (backGroundObejct != nullptr)
	{
		ReserveRemove(backGroundObejct);
	}
}

void EditorScene::RenderSubWin()
{

	D2D1_SIZE_F rtSize = subRenderTarget->GetSize();

	subRenderTarget->BeginDraw();

	subRenderTarget->Clear(D2D1::ColorF(currentColor));
	RenderSubWindow();

	HRESULT hr = subRenderTarget->EndDraw();
}

void EditorScene::OnLeftButtonClicked(Vector clickedPos)
{
	if ((RecievedPreiVewObjectContainer.first.first.empty() || RecievedPreiVewObjectContainer.first.second.empty()) ||
		RecievedPreiVewObjectContainer.second == nullptr)
		return;

	std::string ObjType = RecievedPreiVewObjectContainer.first.first;
	std::string ObjName = RecievedPreiVewObjectContainer.first.second;
	StaticObject* SelectedObj = RecievedPreiVewObjectContainer.second;

	StaticObject* AddedObject = nullptr;

	//플랫폼일 경우
	if (ObjType == "Platform")
	{
		AddedObject = new StaticObject(SpriteManager::GetInstance()->GetTextures(ObjType, ObjName),
			RenderLayer::Platform, SelectedObj->GetPos(), ImageAnchor::Center);

		StaticObjects.push_back(EdiSceneObject(ObjType, ObjName, AddedObject));
	}

	else
	{
		AddedObject = new StaticObject(SpriteManager::GetInstance()->GetTextures(ObjName, "Idle"),
			RenderLayer::Character, SelectedObj->GetPos(), ImageAnchor::Bottomcenter);

		SetCustumAnimSpeed(ObjName, AddedObject);
		LivingObjects.push_back(EdiSceneObject(ObjType, ObjName, AddedObject));
	}

	if (AddedObject)
	{
		ReserveAdd(AddedObject);
	}

}

void EditorScene::OnRightButtonClicked(Vector clickedPos)
{

	{

		int playerNums = 0;
		for (auto& livingObj : LivingObjects)
		{
			if (livingObj.type == "Player")
				playerNums++;
		}


		auto livingObj = LivingObjects.begin();
		while (livingObj != LivingObjects.end())
		{
			Vector ObjectPos = livingObj->obj->GetPos();
			Vector TextureSize = livingObj->obj->animator.GetAnimTexture()->GetTextureSize();

			float halfX = TextureSize.x * 0.5;

			if (clickedPos.x > ObjectPos.x - halfX		   &&
				clickedPos.y > ObjectPos.y - TextureSize.y &&
				clickedPos.x < ObjectPos.x + halfX		   &&
				clickedPos.y < ObjectPos.y)

			{

				if (livingObj->type == "Player")
				{
					if (playerNums > 1)
					{
						ReserveRemove(livingObj->obj);
						livingObj = LivingObjects.erase(livingObj);
						return;
					}
				}

				else
				{
					ReserveRemove(livingObj->obj);
					livingObj = LivingObjects.erase(livingObj);
					return;
				}
				
			}

			livingObj++;
		}
	}
	

	auto staticObj = StaticObjects.begin();
	while (staticObj != StaticObjects.end())
	{
		if (staticObj->name.find("empty") != std::string::npos)
		{
			staticObj++;
			continue;
		}
			

		Vector ObjectPos = staticObj->obj->GetPos();
		Vector TextureSize = staticObj->obj->animator.GetAnimTexture()->GetTextureSize();

		float halfX = TextureSize.x * 0.5;
		float halfY = TextureSize.y * 0.5;

		if (clickedPos.x > ObjectPos.x - halfX &&
			clickedPos.y > ObjectPos.y - halfY &&
			clickedPos.x < ObjectPos.x + halfX &&
			clickedPos.y < ObjectPos.y + halfY)

		{
			ReserveRemove(staticObj->obj);
			staticObj = StaticObjects.erase(staticObj);
			return;
		}

		staticObj++;
	}

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

void EditorScene::ChangeStage(int Inum)
{
	if (currentStage == "Stage1" && Inum < 0)
		return;

	if (currentStage == "Stage3" && Inum > 0)
		return;

	EraseScene();

	currentStage = AddjustStageString(currentStage, Inum);

	ReadStageData(currentStage);

}

bool EditorScene::ReadStageData(std::string stageName)
{
	LivingObjects.clear();
	StaticObjects.clear();

	if (LoadJsonFile(stageName) == false)
		return false;

	return true;
}

bool EditorScene::WriteStageData()
{
	if (LivingObjects.empty() && StaticObjects.empty())
		return false;

	json stageJson;

	if (stageBackGroundName.empty())
		return false;

	stageJson["BackGround"] = stageBackGroundName;

	stageJson["LivingObjects"]["Object"] = json::array();

	//LivingObject 작성
	for (auto& livingObj : LivingObjects)
	{
		stageJson["LivingObjects"]["Object"].push_back({
		{"owner", livingObj.type},
		{"type", livingObj.name},
		{"position", {livingObj.obj->GetPos().x, livingObj.obj->GetPos().y}}
			});
	}


	//StaticObject 작성
	for (auto& staticObj : StaticObjects)
	{
		stageJson["StaticObjects"]["Object"].push_back({
		{"type", staticObj.type},
		{"name", staticObj.name},
		{"position", {staticObj.obj->GetPos().x, staticObj.obj->GetPos().y}}
			});
	}

	//에디터 씬에는 없는 종이 벽 저장
	{
		stageJson["StaticObjects"]["Object"].push_back({
		{"type", "Wall"},
		{"name", "PaperWall"},
		{"position", {80, 350}}
			});

		stageJson["StaticObjects"]["Object"].push_back({
			{"type", "Wall"},
			{"name", "PaperWall"},
			{"position", {1640, 350}}
			});
	}

	std::string Filename = currentStage + ".stage";
	wchar_t buffer[MAX_PATH];
	DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
	fs::path ResourcePath = fs::path(buffer) / L"../../StageInfo/";
	ResourcePath = ResourcePath.lexically_normal();

	fs::path fullFilePath = ResourcePath / fs::path(Filename);

	std::ofstream outFile(fullFilePath);
	if (!outFile.is_open())
	{
		return false;
	}

	outFile << stageJson.dump(4);
	outFile.close();

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
	{
		ReserveAdd(backGroundObejct);
		stageBackGroundName = stageData["BackGround"];
	}


	{
		auto livingObjects = stageData["LivingObjects"]["Object"];
		for (const auto& object : livingObjects)
		{
			std::string owner = object["owner"];
			std::string name = object["type"];
			Vector position = Vector(object["position"][0], object["position"][1]);

			EdiSceneObject character;

			if (owner == "Player")
			{
				character = { "Player", name,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(name, "Idle"),
								RenderLayer::Character, position, ImageAnchor::Bottomcenter) };
			}

			else if (owner == "AI")
			{
				character = { "AI", name,
				new StaticObject(SpriteManager::GetInstance()->GetTextures(name, "Idle"),
								RenderLayer::Character, position, ImageAnchor::Bottomcenter) };
			}

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

bool EditorScene::WriteJsonFile(std::string FileName)
{
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

void EditorScene::SetPrieViewObject(std::pair<std::string, std::string> Objinfo, StaticObject* PreviewObject)
{
	//Null prt이면 그런대로 사용할거다
	RecievedPreiVewObjectContainer.first = Objinfo;
	RecievedPreiVewObjectContainer.second = PreviewObject;
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
				return SendData;
			}
		}
	}

	StopAllSubWinObjAnim();
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
		if (Obj.obj != theExcep->obj)
			Obj.obj->animator.StopAnim();
	}
}

void EditorScene::StopAllSubWinObjAnim()
{

	for (auto& Obj : SubWinObject[0])
	{
		Obj.obj->animator.StopAnim();
	}

}

std::string EditorScene::AddjustStageString(std::string stageName, int addmount)
{
	size_t pos = currentStage.find_last_of("0123456789");
	if (pos != std::string::npos) {

		int number = std::stoi(currentStage.substr(pos));
		number += addmount;

		std::string newStr = currentStage.substr(0, pos) + std::to_string(number);

		currentStage = newStr;

		return currentStage;
	}
}

void EditorScene::ChangeColor()
{

	auto CompareColor = [](const D2D1::ColorF& c1, const D2D1::ColorF& c2) -> bool
		{
			const float EPSILON = 0.001f;
			return fabs(c1.r - c2.r) < EPSILON &&
				fabs(c1.g - c2.g) < EPSILON &&
				fabs(c1.b - c2.b) < EPSILON &&
				fabs(c1.a - c2.a) < EPSILON;
		};

	if (CompareColor(currentColor, D2D1::ColorF::Coral))
		currentColor = D2D1::ColorF::Aqua;

	else if(CompareColor(currentColor, D2D1::ColorF::Aqua))
		currentColor = D2D1::ColorF::Coral;


	//if (num == true)
	//{
	//	//if(currentColor == D2D1::ColorF::Coral)
	//	if (CompareColor(currentColor, D2D1::ColorF::Coral))
	//	{
	//		return;
	//	}

	//	else
	//	{
	//		currentColor = D2D1::ColorF::Coral;
	//	}
	//}

	//else if (num == false)
	//{
	//	if (CompareColor(currentColor, D2D1::ColorF::Aqua))
	//	{
	//		return;
	//	}

	//	else
	//	{
	//		currentColor = D2D1::ColorF::Aqua;
	//	}
	//}

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
