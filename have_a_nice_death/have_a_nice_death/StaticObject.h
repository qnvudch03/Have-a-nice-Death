#pragma once
#include "Object.h"

class StaticObject : public Object
{
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	StaticObject(std::vector<Texture*>* OwningTextures, RenderLayer RenderType, Vector pos = Vector(0,0), bool drawCenter = false) : Super(RenderType, drawCenter)
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

