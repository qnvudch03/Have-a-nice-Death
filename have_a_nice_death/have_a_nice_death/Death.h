#pragma once
#include "LivingObject.h"
class Death : public LivingObject
{
	using Super = LivingObject;

public:

	Death(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, DrawAnchor anchorPosition = DrawAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition = DrawAnchor::Topleft)
	{
		SetState("Ideal");
		animaotr.SetAnimSpeed(30);

		//Setstae¶û Speed °ª ¼³Á¤ÇØ!!
	}

	~Death() {}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

private:
	//Controller controller;
};

