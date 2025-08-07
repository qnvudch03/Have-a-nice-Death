#pragma once
#include "Scene.h"
#include "Stage.h"

class Object;
class Controller;
class PlayerController;
class AIController;
class LivingObject;

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

	void BindController(Controller* controller, LivingObject* ownerObject);
	void ChangeControllerOwner(Controller* controller, LivingObject* newownerObject);
	void LoadStage(std::string stage);

	std::vector<Object*>* GetGameSceneObjectVec() { return &_gameSceneObjects; }



private:

	//�÷��̾� <-> ��Ʈ�ѷ� �̷������� ���εǰ�
	std::map< Controller* , LivingObject*> _gameControllerMap;

	//���� ����������������� ��� ������Ʈ���� ����ִ�.
	std::vector<Object*> _gameSceneObjects;

	std::vector<PlayerController*> _playerControllerVec;
	std::vector< AIController*> _aiControllerVec;

	Stage* stageController = nullptr;
	//std::vector<Object*> _gameSceneObjects;
};

