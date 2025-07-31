#pragma once
#include "Scene.h"
#include "Object.h"

class Lobby : public Scene
{
	using Super = Scene;

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void PostUpdate(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* renderTarget) override;

protected:
	virtual void loadResource() override;

	std::vector<Object*> LobbySceneObjects;

	Object* _backGround = nullptr;

	Object* _Death_Head = nullptr;
	Object* _Death_Body = nullptr;
	Object* _Death_Arm = nullptr;
	Object* _smoke = nullptr;

	Object* _Start_Btn = nullptr;
	Object* _Edit_Btn = nullptr;
};

