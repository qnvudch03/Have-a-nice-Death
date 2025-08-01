#pragma once
#include "Object.h"

class StaticObject : public Object
{
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;
	StaticObject(std::vector<Texture*>* OwningTextures, RenderLayer RenderType, Vector pos = Vector(0,0), DrawAnchor drawAncor = DrawAnchor::Topleft) : Super(RenderType, drawAncor)
	{
		_ownTextures = OwningTextures;
		Super::SetPlayTexture(_ownTextures);
		Super::SetPos(pos);
	}

	~StaticObject()
	{

	}


private:
	std::vector<Texture*>* _ownTextures = nullptr;
};

