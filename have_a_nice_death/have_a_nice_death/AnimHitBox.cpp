#include "pch.h"
#include "AnimHitBox.h"
#include "LivingObject.h"
#include "Game.h"
#include "GameScene.h"
#include "HitBoxManager.h"

void AnimHitBox::Update(float deltatime)
{
	//stackTimer += deltatime;

	animator.Update(deltatime);
}

void AnimHitBox::ClearBox()
{
	animator.SetAnimTexture(nullptr, false);

	pos = { 0,0 };
	size = { 0,0 };
	type = HitBoxType::Default_HitBox;
	//stackTimer = 0;
}

void AnimHitBox::SetAnimHitBox(Vector Pos, Vector Size, float Damage, HitBoxType Type, bool IsPlayerHitBox, LivingObject* Spawner)
{
	pos = Pos;
	size = Size;
	type = Type;

	damage = Damage;

	isPlayerHitBox = IsPlayerHitBox;

	spawner = Spawner;

	forwordDirection = (spawner->GetPos().x <= pos.x) ? 1 : -1;
}

void AnimHitBox::OnAnimEnd()
{
	ClearBox();

	static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager()->ReturnHitBox(this);
}
