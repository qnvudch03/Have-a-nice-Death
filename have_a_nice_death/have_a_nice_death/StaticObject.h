#pragma once
#include "Object.h"

class StaticObject : public Object
{
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;
	StaticObject(std::vector<Texture*>* OwningTextures, RenderLayer RenderType, Vector pos = Vector(0,0), ImageAnchor drawAncor = ImageAnchor::Topleft) : Super(RenderType, drawAncor)
	{
		_ownTextures = OwningTextures;
		Super::SetAnimaotrTextures(_ownTextures);
		Super::SetPos(pos);
	}

	~StaticObject()
	{

	}


private:
	std::vector<Texture*>* _ownTextures = nullptr;
};

