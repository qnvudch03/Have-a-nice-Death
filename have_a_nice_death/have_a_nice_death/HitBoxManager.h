#pragma once

#include "HitBox.h"
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
		spanwedHitBoxVec.insert(hitbox);

		currentGameScene = Game::GetInstance()->GetGameScene();
	}
	void ReturnHitBox(HitBox* hitbox);
	void CheckCollision(HitBox* hitbox);
	void Update(float deltatime);

private:
	std::queue<HitBox*> hitBoxPull;
	std::set<HitBox*> spanwedHitBoxVec;

	GameScene* currentGameScene = nullptr;
};

