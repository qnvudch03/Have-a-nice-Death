#include "pch.h"
#include "HitBox.h"
#include "Game.h"
#include "Scene.h"
#include "GameScene.h"
#include "HitBoxManager.h"
#include "LivingObject.h"

void HitBox::SetHitBox(Vector Pos, Vector Size, float Damage, HitBoxType Type, float LifeTime, bool IsPlayerHitBox, LivingObject* Spawner)
{
	pos = Pos;
	size = Size;
	type = Type;
	lifeTime = LifeTime;

	damage = Damage;

	isPlayerHitBox = IsPlayerHitBox;

	spawner = Spawner;

	forwordDirection = (spawner->GetPos().x <= pos.x) ? 1 : -1;
}

void HitBox::ClearBox()
{
	pos = { 0,0 };
	size = { 0,0 };
	type = HitBoxType::Default_HitBox;
	lifeTime = 0;
	stackTimer = 0;
}

void HitBox::Update(float deltatime)
{
	stackTimer += deltatime;



	if (stackTimer >= lifeTime)
	{
		ClearBox();

		static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager()->ReturnHitBox(this);
	}


}