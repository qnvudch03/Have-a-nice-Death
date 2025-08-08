#pragma once
#include "LivingObject.h"
#include "InputManager.h"

class Texture;

class SmallGhost : public LivingObject
{

	using Super = LivingObject;

public:

	SmallGhost(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft)
		: Super(OwningTextures, RenderType, anchorPosition)
	{

	}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void OnAnimEnd() override;

private:

};

