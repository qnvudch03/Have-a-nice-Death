#pragma once
#include "Object.h"

class LivingObject;
class GameScene;

class InteractableObject : public Object
{
	using Super = Object;

	enum MyEnum
	{

	};

public:
	InteractableObject(RenderLayer rendertype, ImageAnchor drawanchor, Vector pos);
	virtual void Update(float deltaTime) override;

	virtual void DoInteract() {}
	virtual void OnAnimEnd() {}
	virtual void SetDebugMode(bool debugmode) override;

	bool GetReadyToInteract() { return readyToInteract; }

protected:
	bool readyToInteract = false;
	bool activate = false;
	LivingObject* player = nullptr;
	GameScene* gameScene = nullptr;

};

