#include "pch.h"
#include "Animaotr.h"

void Animator::Update(float deltaTime)
{
	_animStackTimer += deltaTime * _animSpeed;

	if (_animStackTimer >= TextureNum)
		_animStackTimer = 0;

	AnimTextureIndex = (int32)_animStackTimer;
}

void Animator::Destroy()
{
	auto Iter = (*_animTextures).begin();

	while (Iter != (*_animTextures).end())
	{
		delete (*Iter);
		Iter++;
	}
}
