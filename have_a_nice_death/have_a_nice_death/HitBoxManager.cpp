#include "pch.h"
#include "HitBoxManager.h"
#include "HitBox.h"

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

	auto a = spanwedHitBoxVec;
	for (auto Iter : a)
	{
		Iter->Update(deltatime);
	}
}