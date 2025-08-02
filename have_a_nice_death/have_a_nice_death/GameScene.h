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

	//플레이어 <-> 컨트롤러 이런식으로 매핑되게
	std::map< Controller* , LivingObject*> _gameControllerMap;

	//게임에서 사용할 모든 오브젝트들이 들어있다.
	std::map<std::string, Object*> _gameSceneObjects;

	//현재 스테이지에서 사용 할 오브젝트들이 들어있다.

	std::vector<PlayerController*> _playerControllerVec;
	std::vector< AIController*> _aiControllerVec;
	//std::vector<Object*> _gameSceneObjects;
};

