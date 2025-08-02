#pragma once
#include "Scene.h"

class Object;
class Controller;
class PlayerController;
class AIController;
class LivingObject;

class GameScene : public Scene
{
	struct GameSceneObject
	{
		inline static const std::string Death = "Death";
		inline static const std::string Monster = "Monster";
	};

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

private:

	//�÷��̾� <-> ��Ʈ�ѷ� �̷������� ���εǰ�
	std::map< Controller* , LivingObject*> _gameControllerMap;

	//���ӿ��� ����� ��� ������Ʈ���� ����ִ�.
	std::map<std::string, Object*> _gameSceneObjects;

	//���� ������������ ��� �� ������Ʈ���� ����ִ�.

	std::vector<PlayerController*> _playerControllerVec;
	std::vector< AIController*> _aiControllerVec;
	//std::vector<Object*> _gameSceneObjects;
};

