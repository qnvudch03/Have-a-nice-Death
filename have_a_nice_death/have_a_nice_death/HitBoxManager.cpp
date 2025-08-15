#include "pch.h"
#include "HitBoxManager.h"
#include "HitBox.h"
#include "Object.h"
#include "Collider.h"
#include "LivingObject.h"
#include "Controller.h"
#include "Game.h"
#include "DebugLenderer.h"

HitBoxManager::~HitBoxManager()
{
	if (!spanwedHitBoxVec.empty())
	{
		for (auto Iter : spanwedHitBoxVec)
		{
			delete Iter;
		}

		spanwedHitBoxVec.clear();
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

	if (!spanwedAnimHitBoxVec.empty())
	{
		for (auto Iter : spanwedAnimHitBoxVec)
		{
			delete Iter;
		}

		spanwedAnimHitBoxVec.clear();
	}

	if (!animHitBoxPull.empty())
	{
		while (!animHitBoxPull.empty())
		{
			AnimHitBox* hitbox = animHitBoxPull.front();
			animHitBoxPull.pop();

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

	for (int i = 0; i < 20; i++)
	{
		animHitBoxPull.push(new AnimHitBox());
	}

	currentGameScene = Game::GetInstance()->GetGameScene();
}

HitBox* HitBoxManager::CallHitBox()
{
	if (!hitBoxPull.empty())
	{
		HitBox* hitBox = hitBoxPull.front();
		hitBoxPull.pop();
		return hitBox;

	}

	return nullptr;
}

AnimHitBox* HitBoxManager::CallAnimHitBox()
{
	if (!animHitBoxPull.empty())
	{
		AnimHitBox* hitBox = animHitBoxPull.front();
		animHitBoxPull.pop();
		return hitBox;

	}

	return nullptr;
}

void HitBoxManager::ReturnHitBox(HitBox* hitbox)
{
	if (hitbox == nullptr)
		return;

	hitBoxPull.push(hitbox);
	spanwedHitBoxVec.erase(hitbox);
}

void HitBoxManager::ReturnAnimHitBox(AnimHitBox* hitbox)
{
	if (hitbox == nullptr)
		return;

	animHitBoxPull.push(hitbox);
	spanwedAnimHitBoxVec.erase(hitbox);
}

void HitBoxManager::Update(float deltatime)
{

	if (!spanwedHitBoxVec.empty())
	{
		auto hitBox = spanwedHitBoxVec;
		for (auto Iter : hitBox)
		{
			Iter->Update(deltatime);
			CheckCollision(Iter);

		}

	}

	if (!spanwedAnimHitBoxVec.empty())
	{
		auto animHitBox = spanwedAnimHitBoxVec;
		for (auto Iter : animHitBox)
		{
			Iter->Update(deltatime);
			CheckCollision(Iter);
		}
	}

	
}

void HitBoxManager::DrawHitbox(ID2D1RenderTarget* renderTarget)
{
	//spanwedHitBoxVec
	bool isDbugMode = Game::GetInstance()->GetCurrentScence()->IsDbugMode;
	auto GarbageCollector = Game::GetInstance()->GetDebugLenderer();

	if (!spanwedAnimHitBoxVec.empty())
	{
		for (auto& Iter : spanwedAnimHitBoxVec)
		{
			bool Fliporder = (Iter->GetForwordDirection() == 1) ? false : true;
			Iter->animator.GetAnimTexture()->Render(renderTarget, Iter->GetPos(), ImageAnchor::Center, Fliporder);

			if (isDbugMode)
			{
				GarbageCollector->ReservedHitBox(Iter);
			}
		}
	}
}

void HitBoxManager::CheckCollision(HitBox* hitbox)
{
	for (auto object : *(currentGameScene->GetGameSceneObjectVec()))
	{
		if (object->GetRenderLayer() != RenderLayer::Character || object->collider == nullptr)
			continue;

		LivingObject* character = static_cast<LivingObject*>(object);
		if (character->GetController()->isPlayerController == hitbox->isPlayerHitBox)
			continue;

		if (!object->collider->CheckIsActive())
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
			character->Hitted(hitbox);
		}

	}
}