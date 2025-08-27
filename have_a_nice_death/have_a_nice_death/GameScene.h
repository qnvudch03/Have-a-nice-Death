#pragma once
#include "Scene.h"
#include "Stage.h"


class Object;
class Controller;
class PlayerController;
class AIController;
class LivingObject;
class HitBoxManager;
class UIButton;
class EffectManager;

class GameScene : public Scene
{

	using Super = Scene;

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void PostUpdate(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;
	virtual void EraseScene() override;

	EffectManager* GetEffectManager() { return effectManager; }

	virtual void loadResource() override;
	virtual void loadUI() override;

	void MappingInGameFunction();
	void BindController(Controller* controller, LivingObject* ownerObject);
	void ChangeControllerOwner(Controller* controller, LivingObject* newownerObject);
	void LoadStage(std::string stage);
	void LoadObject(Object* obj);
	void EraseFromGame(Object* obj);

	std::string GetNextStage();
	void SetUI_PlayGame();
	void SetUI_SelectReword();
	void SetUI_GameOver();
	void SetUI_ClearGame();
	void SetUI_EndingScene();

	void SavePlayData();

	Stage* GetStage() { return stageController; }
	void GoNextStage();

	HitBoxManager* GetHitBoxManager() { return hitBoxManager; }

	std::vector<Object*>* GetGameSceneObjectVec() { return &_gameSceneObjects; }

	std::map<std::string, float> playerSaveParam
	{
		{"actionSpeed", 1.0},
		{"atkBonus",	0.0},
		{"defBonus",	0.0},
		{"currentHP",	1.0},
		{"dashCollTime",1.0}
	};

private:

	//플레이어 <-> 컨트롤러 이런식으로 매핑되게
	std::map< Controller* , LivingObject*> _gameControllerMap;

	//현재 스테이지에서사용할 모든 오브젝트들이 들어있다.
	std::vector<Object*> _gameSceneObjects;

	std::vector<PlayerController*> _playerControllerVec;
	std::vector< AIController*> _aiControllerVec;

	Stage* stageController = nullptr;
	HitBoxManager* hitBoxManager = nullptr;
	EffectManager* effectManager = nullptr;

	//인게임 액션 맵
	std::map<std::string, std::function<void()>> _inGameActionMap;
	void BindingWithBtn();

	void Curse_Attack();
	void Curse_ActionSpeed();
	void Curse_DashCoolTime();
	void Curse_Deffense();
	void Curse_Healing();

	int stage_count = 0;

	std::vector< UIButton*> Curse_List;
};

