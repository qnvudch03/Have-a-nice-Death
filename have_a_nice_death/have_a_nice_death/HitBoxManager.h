#pragma once

#include "HitBox.h"
#include "AnimHitBox.h"
#include "Scene.h"
#include "Game.h"
#include "GameScene.h"

class HitBoxManager
{
public:
	HitBoxManager(){}
	~HitBoxManager();

	void Init();

	HitBox* CallHitBox();
	void AddHitBox(HitBox* hitbox)
	{
		if (hitbox == nullptr)
			return;
		spanwedHitBoxVec.insert(hitbox);
	}

	AnimHitBox* CallAnimHitBox();

	void AddAnimHitBox(AnimHitBox* hitbox, ImageAnchor HitBoxAnchor)
	{
		spanwedAnimHitBoxVec.insert(std::make_pair(hitbox, HitBoxAnchor));
		hitbox->hitBoxAncor = HitBoxAnchor;
	}


	void ReturnHitBox(HitBox* hitbox);
	void ReturnAnimHitBox(AnimHitBox* hitbox);

	void CheckCollision(HitBox* hitbox);
	void Update(float deltatime);

	void DrawHitbox(ID2D1RenderTarget* renderTarget);

private:
	std::queue<HitBox*> hitBoxPull;
	std::set<HitBox*> spanwedHitBoxVec;

	std::queue<AnimHitBox*> animHitBoxPull;
	std::set<std::pair<AnimHitBox*, ImageAnchor>> spanwedAnimHitBoxVec;

	GameScene* currentGameScene = nullptr;
};

