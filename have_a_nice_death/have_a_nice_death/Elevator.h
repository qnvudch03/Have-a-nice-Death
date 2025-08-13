#pragma once
#include "StaticObject.h"

class Elevator : public StaticObject
{
	using Super = StaticObject;

public:
	Elevator(std::vector<Texture*>* OwningTextures, RenderLayer RenderType, Vector pos = Vector(0, 0), ImageAnchor drawAncor = ImageAnchor::Bottomcenter) :
		Super(OwningTextures, RenderType, pos, drawAncor)
	{
		animator.SetAnimLoop(false);
		animator.SetAnimSpeed(20);

		collider->DeActivateCollier();
	}

	int callCount = 0;
;private:

};

