#include "pch.h"
#include "Effect.h"
#include "Game.h"
#include "GameScene.h"
#include "EffectManager.h"

void Effecter::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Effecter::SetEffect(std::vector<Texture*>* OwningTextures, Vector pos, float animSpeed)
{
	SetPos(pos);
	animator.ResetAnimTimer(animSpeed);
	animator.onAnimEnd = [this]() {this->OnEffectEnd(); };
	animator.StartAnim();

	SetAnimaotrTextures(OwningTextures, false);
}

void Effecter::Clear()
{
}

void Effecter::OnEffectEnd()
{
	Game::GetInstance()->GetGameScene()->GetEffectManager()->ReturnEffect(this);
	Game::GetInstance()->GetGameScene()->ReserveRemove(this);
}
