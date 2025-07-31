#include "pch.h"
#include "Animaotr.h"

void Animaotr::Update(float deltaTime)
{
	_animStackTimer += deltaTime * _animSpeed;

	if (_animStackTimer >= TextureNum)
		_animStackTimer = 0;

	AnimTextureIndex = (int32)_animStackTimer;
}
