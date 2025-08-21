#pragma once
#include "Scene.h"

class StaticObject;

class EditorScene : public Scene
{
	using Super = Scene;

	//std::string CharacterOjbectList[3] = {"Death", "SmallGhost", "MedGhost"};
	std::string CharacterOjbectList[3] = { "Death", "SmallGhost"};

	struct EdiSceneObject
	{
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

private:

	void SetCustumAnimSpeed(std::string name, StaticObject* obj);

	/*std::vector<EdiSceneObject> SubWinCharacterObject;
	std::vector<EdiSceneObject> SubWinStaticObject;*/

	//0에는 Chracter 1에는 staticObject
	std::vector<EdiSceneObject> SubWinObject[2];

	std::vector<EdiSceneObject> LivingObjects;
	std::vector<EdiSceneObject> StaticObjects;
	StaticObject* backGroundObejct = nullptr;

	std::string currentStage;

	ID2D1RenderTarget* subRenderTarget = nullptr;
	HWND	_subhwnd = nullptr;
};

