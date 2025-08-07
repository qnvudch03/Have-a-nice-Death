#pragma once
#include "Object.h"
#include "Collider.h"

class StaticObject : public Object
{
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;
	virtual void SetCollider() override;
	StaticObject(std::vector<Texture*>* OwningTextures, RenderLayer RenderType, Vector pos = Vector(0,0), ImageAnchor drawAncor = ImageAnchor::Topleft) : Super(RenderType, drawAncor)
	{
		_ownTextures = OwningTextures;
		Super::SetAnimaotrTextures(_ownTextures);
		Super::SetPos(pos);

		SetCollider();

		if (collider != nullptr)
			collider->InitPos();
	}

	~StaticObject()
	{

	}


private:
	std::vector<Texture*>* _ownTextures = nullptr;
};

