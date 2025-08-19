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

	virtual void loadResource() override;
	virtual void loadUI() override;

	void MappingInGameFunction();
	void BindController(Controller* controller, LivingObject* ownerObject);
	void ChangeControllerOwner(Controller* controller, LivingObject* newownerObject);
	void LoadStage(std::string stage);
	void LoadObject(Object* obj);
	void EraseFromGame(Object* obj);

	void SetUI_PlayGame();
	void SetUI_SelectReword();

	Stage* GetStage() { return stageController; }

	HitBoxManager* GetHitBoxManager() { return hitBoxManager; }

	std::vector<Object*>* GetGameSceneObjectVec() { return &_gameSceneObjects; }

private:

	//�÷��̾� <-> ��Ʈ�ѷ� �̷������� ���εǰ�
	std::map< Controller* , LivingObject*> _gameControllerMap;

	//���� ����������������� ��� ������Ʈ���� ����ִ�.
	std::vector<Object*> _gameSceneObjects;

	std::vector<PlayerController*> _playerControllerVec;
	std::vector< AIController*> _aiControllerVec;

	Stage* stageController = nullptr;
	HitBoxManager* hitBoxManager = nullptr;

	//�ΰ��� �׼� ��
	std::map<std::string, std::function<void()>> _inGameActionMap;
	void BindingWithBtn();

	void Curse_Attack();
	void Curse_ActionSpeed();
	void Curse_DashCoolTime();
	void Curse_Deffense();
	void Curse_Healing();

	std::vector< UIButton*> Curse_List;
};

