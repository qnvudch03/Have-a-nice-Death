#include "pch.h"
#include "EffectManager.h"

EffectManager::EffectManager()
{
    for (int i = 0; i < 30; i++)
    {
        effectqueue.push(new Effecter());
    }
}

void EffectManager::Update(float deltatime)
{
    for (auto& Obj : spawnedEffect)
    {
        Obj->Update(deltatime);
    }
}

Effecter* EffectManager::CallEffect()
{
    if (effectqueue.empty())
        return nullptr;

    Effecter* effect = effectqueue.front();
    spawnedEffect.insert(effect);
    effectqueue.pop();

    return effect;
}

void EffectManager::EraseEffects()
{
    while (effectqueue.empty())
    {
        Effecter* effect = effectqueue.front();
        effectqueue.pop();

        delete effect;
    }

    for (auto effect : spawnedEffect)
    {
        delete effect;
    }

    spawnedEffect.clear();
}

void EffectManager::ReturnEffect(Effecter* effect)
{
    if (effect == nullptr)
        return;

    effect->SetPos({ 0,0 });
    effect->animator.SetAnimTexture(nullptr, false);
    effect->animator.onAnimEnd = nullptr;
    effect->animator.StopAnim();


    effectqueue.push(effect);
}
