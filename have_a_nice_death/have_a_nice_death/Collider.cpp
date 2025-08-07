#include "pch.h"
#include "Collider.h"
#include "Object.h"

void Collider::Update()
{
	if (owner->GetRenderLayer() == RenderLayer::Platform)
	{
		pos = owner->GetPos();

		float halfX = size.x * 0.5f;
		float halfY = size.y * 0.5f;

		rectangle.TopLeft.x = pos.x - halfX;
		rectangle.TopLeft.y = pos.y - halfY;

		rectangle.TopRight.x = pos.x + halfX;
		rectangle.TopRight.y = pos.y - halfY;

		rectangle.BottomLeft.x = pos.x - halfX;
		rectangle.BottomLeft.y = pos.y + halfY;

		rectangle.BottomRight.x = pos.x + halfX;
		rectangle.BottomRight.y = pos.y + halfY;
	}

	else if (owner->GetRenderLayer() == RenderLayer::Character)
	{
		pos = owner->GetPos();

		float halfX = size.x * 0.5f;
		float halfY = size.y * 0.5f;

		rectangle.TopLeft.x = pos.x - halfX;
		rectangle.TopLeft.y = pos.y - size.y;

		rectangle.TopRight.x = pos.x + halfX;
		rectangle.TopRight.y = pos.y - size.y;

		rectangle.BottomLeft.x = pos.x - halfX;
		rectangle.BottomLeft.y = pos.y;

		rectangle.BottomRight.x = pos.x + halfX;
		rectangle.BottomRight.y = pos.y;
	}
	

}

void Collider::InitPos()
{
	Update();
}
