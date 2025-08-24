#pragma once
#include "Scene.h"

#include <functional>

class StaticObject;
class WindowMediator;

class EditorScene : public Scene
{
	using Super = Scene;

	std::string CharacterOjbectList[4] = {"Death", "SmallGhost", "MedGhost", "Boss_W7"};

	struct EdiSceneObject
	{
		std::string type;
		std::string name;

		StaticObject* obj;
	};

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void PostUpdate(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
	virtual void EraseScene() override;
	virtual void RenderSubWin() override;

	virtual void OnLeftButtonClicked(Vector clickedPos) override;
	virtual void OnRightButtonClicked(Vector clickedPos) override;


	void SetSubWindow(ID2D1RenderTarget* SubRenderTarget, HWND	Subhwnd);
	void LoadSubWinObject();
	void RenderSubWindow();
	void ChangeStage(int num);
	bool ReadStageData(std::string stageName);
	bool WriteStageData();

	bool LoadJsonFile(std::string FileName);
	bool WriteJsonFile(std::string FileName);



	//서브윈도우랑 통신하는 액트
	void AddWinOffset(Vector amount);
	void ChangeColor();

	void SetPrieViewObject(std::pair<std::string, std::string> Objinfo, StaticObject* PreviewObject);
	std::pair<std::string, std::string> GetSellectedEdiSceneObjectData();

	std::function<void()> onStageReRoad = nullptr;

	Vector subWinMouseClickedPos;


private:

	void SetCustumAnimSpeed(std::string name, StaticObject* obj);
	void StopAllSubWinObjAnimExcep(EdiSceneObject* theExcep);
	void StopAllSubWinObjAnim();

	//0에는 Chracter 1에는 staticObject
	//서브윈도우에 표시 할, 오브젝트들 있는 곳
	std::vector<EdiSceneObject> SubWinObject[2];

	std::string AddjustStageString(std::string stageName, int addmount);

	std::vector<EdiSceneObject> LivingObjects;
	std::vector<EdiSceneObject> StaticObjects;
	StaticObject* backGroundObejct = nullptr;
	std::string stageBackGroundName;

	std::string currentStage;

	std::pair<std::pair<std::string, std::string>, StaticObject*> RecievedPreiVewObjectContainer;

	D2D1::ColorF currentColor = D2D1::ColorF::Coral;

	WindowMediator* winMediator = nullptr;

	ID2D1RenderTarget* subRenderTarget = nullptr;
	HWND	_subhwnd = nullptr;

	Vector subWinOffset = Vector(0,0);
	int WinOffsetYMax = 0;
};

