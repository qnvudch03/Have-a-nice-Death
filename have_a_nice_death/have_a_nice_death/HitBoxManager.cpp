#include "pch.h"
#include "HitBoxManager.h"
#include "HitBox.h"
#include "Object.h"
#include "Collider.h"
#include "LivingObject.h"
#include "Controller.h"

HitBoxManager::~HitBoxManager()
{
	if (!spanwedHitBoxVec.empty())
	{
		for (auto Iter : spanwedHitBoxVec)
		{
			delete Iter;
		}
	}

	if (!hitBoxPull.empty())
	{
		while (!hitBoxPull.empty())
		{
			HitBox* hitbox = hitBoxPull.front();
			hitBoxPull.pop();

			delete hitbox;
		}
	}
	
}

void HitBoxManager::Init()
{
	for (int i = 0; i < 20; i++)
	{
		hitBoxPull.push(new HitBox());
	}
}

HitBox* HitBoxManager::CallHitBox()
{
	if (!hitBoxPull.empty())
	{
		HitBox* hitBox = hitBoxPull.front();
		hitBoxPull.pop();
		return hitBox;

	}
}

void HitBoxManager::ReturnHitBox(HitBox* hitbox)
{
	if (hitbox == nullptr)
		return;

	hitBoxPull.push(hitbox);
	spanwedHitBoxVec.erase(hitbox);
}

void HitBoxManager::Update(float deltatime)
{
	if (spanwedHitBoxVec.empty())
		return;

	auto hitBox = spanwedHitBoxVec;
	for (auto Iter : hitBox)
	{
		Iter->Update(deltatime);
		CheckCollision(Iter);
	}
}

void HitBoxManager::CheckCollision(HitBox* hitbox)
{
	for (auto object : *(currentGameScene->GetGameSceneObjectVec()))
	{
		if (object->GetRenderLayer() != RenderLayer::Character)
			continue;

		LivingObject* character = static_cast<LivingObject*>(object);
		if (character->GetController()->isPlayerController == hitbox->isPlayerHitBox)
			continue;

		RectanglePos characterRec = object->collider->Getrectangle();

		float charMinX = characterRec.TopLeft.x;
		float charMaxX = characterRec.BottomRight.x;
		float charMinY = characterRec.TopLeft.y;
		float charMaxY = characterRec.BottomRight.y;

		Vector boxPos = hitbox->GetPos();
		Vector boxSize = hitbox->GetSize();

		float boxHalfW = boxSize.x * 0.5f;
		float boxHalfH = boxSize.y * 0.5f;

		float boxMinX = boxPos.x - boxHalfW;
		float boxMaxX = boxPos.x + boxHalfW;
		float boxMinY = boxPos.y - boxHalfH;
		float boxMaxY = boxPos.y + boxHalfH;

		bool isColliding = !(boxMaxX < charMinX ||
			boxMinX > charMaxX ||
			boxMaxY < charMinY ||
			boxMinY > charMaxY);

		if (isColliding && character->DamagedAble)
		{
			character->OnHitted(hitbox);
		}

	}
}