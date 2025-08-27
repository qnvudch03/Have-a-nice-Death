#pragma once
#include "Object.h"
#include "Texture.h"
class Effecter : public Object
{
	using Super = Object;
public:
	Effecter() : Super(RenderLayer::Effect, ImageAnchor::Center)
	{
		
	}

	virtual void Update(float deltaTime) override;

	void SetEffect(std::vector<Texture* >* OwningTextures, Vector pos, float animSpeed);
	void Clear();

	void OnEffectEnd();
private:

};

