#include "pch.h"
#include "Collider.h"
#include "Object.h"

void Collider::DeActivateCollier()
{
	isActivated = false;

	{
		pos.x = 0;
		pos.y = 0;

		colliderCenterPos.x = -100;
		colliderCenterPos.y = -100;

		rectangle.TopLeft.x = -100;
		rectangle.TopLeft.y = -100;

		rectangle.TopRight.x = -100;
		rectangle.TopRight.y = -100;

		rectangle.BottomLeft.x = -100;
		rectangle.BottomLeft.y = -100;

		rectangle.BottomRight.x = -100;
		rectangle.BottomRight.y = -100;
	}
}

void Collider::ActivateCollier()
{
	isActivated = true;
}

void Collider::Update()
{
	if (!isActivated)
		return;

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

	colliderCenterPos.x = rectangle.TopLeft.x + size.x * 0.5f;
	colliderCenterPos.y = rectangle.TopLeft.y + size.y * 0.5f;
}

void Collider::InitPos()
{
	Update();
}
