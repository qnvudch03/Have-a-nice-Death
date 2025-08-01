#pragma once
#include "Scene.h"

class Object;

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

private:

	std::map<std::string, Object*> _gameSceneObjects;
	//std::vector<Object*> _gameSceneObjects;
};

