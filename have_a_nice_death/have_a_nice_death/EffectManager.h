#pragma once
#include "Effect.h"

class EffectManager
{
public:
	EffectManager();

	void Update(float deltatime);

	Effecter* CallEffect();
	void EraseEffects();
	void ReturnEffect(Effecter* effect);

private:
	std::queue<Effecter*> effectqueue;
	std::set< Effecter*> spawnedEffect;
};

