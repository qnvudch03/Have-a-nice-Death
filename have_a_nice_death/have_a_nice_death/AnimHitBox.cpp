#include "pch.h"
#include "AnimHitBox.h"
#include "LivingObject.h"
#include "Game.h"
#include "GameScene.h"
#include "HitBoxManager.h"

void AnimHitBox::Update(float deltatime)
{
	//stackTimer += deltatime;

	size = animator.GetAnimTexture()->GetTextureSize() * 0.5;

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

void AnimHitBox::SetAnimHitBox(Vector Pos, Vector Size, std::vector<Texture*>* animtures, float Damage, HitBoxType Type, bool IsPlayerHitBox, LivingObject* Spawner)
{
	pos = Pos;
	size = Size;
	type = Type;

	damage = Damage;

	isPlayerHitBox = IsPlayerHitBox;

	spawner = Spawner;

	forwordDirection = (spawner->GetPos().x <= pos.x) ? 1 : -1;

	animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
	animator.SetAnimTexture(animtures, false);
	animator.TextureNum = (*animtures).size();
}

void AnimHitBox::OnAnimEnd()
{
	ClearBox();

	static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager()->ReturnAnimHitBox(this);
}
