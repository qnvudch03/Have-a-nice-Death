#pragma once
#include "Scene.h"

class StaticObject;

class EditorScene : public Scene
{
	using Super = Scene;

	std::string CharacterOjbectList[3] = {"Death", "SmallGhost", "MedGhost"};
	//std::string CharacterOjbectList[3] = { "Death", "SmallGhost"};

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

	void SetSubWindow(ID2D1RenderTarget* SubRenderTarget, HWND	Subhwnd);
	void LoadSubWinObject();
	void RenderSubWindow();
	bool ReadStageData(std::string stageName);

	bool LoadJsonFile(std::string FileName);



	//서브윈도우랑 통신하는 액트
	void AddWinOffset(Vector amount);
	void ChangeColor(bool num);
	std::pair<std::string, std::string> GetSellectedEdiSceneObjectData();

	Vector subWinMouseClickedPos;


private:

	void SetCustumAnimSpeed(std::string name, StaticObject* obj);
	void StopAllSubWinObjAnimExcep(EdiSceneObject* theExcep);

	//0에는 Chracter 1에는 staticObject
	std::vector<EdiSceneObject> SubWinObject[2];

	std::vector<EdiSceneObject> LivingObjects;
	std::vector<EdiSceneObject> StaticObjects;
	StaticObject* backGroundObejct = nullptr;

	std::string currentStage;

	D2D1::ColorF currentColor = D2D1::ColorF::Coral;

	ID2D1RenderTarget* subRenderTarget = nullptr;
	HWND	_subhwnd = nullptr;

	Vector subWinOffset = Vector(0,0);
	int WinOffsetYMax = 0;
};

