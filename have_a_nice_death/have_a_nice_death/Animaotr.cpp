#include "pch.h"
#include "Animaotr.h"

void Animator::Update(float deltaTime)
{
	if (onPlay == false)
		return;

	_animStackTimer += deltaTime * _animSpeed;

	if (_IsLoop && _animStackTimer >= TextureNum)
		_animStackTimer = 0;

	else if (_IsLoop == false && (int32)_animStackTimer > TextureNum - 1)
	{
		onPlay = false;
		_animStackTimer = TextureNum - 1;
		onAnimEnd();
	}

	AnimTextureIndex = (int32)_animStackTimer;
}

void Animator::Destroy()
{
	//not work
	/*auto Iter = (*_animTextures).begin();

	while (Iter != (*_animTextures).end())
	{
		delete (*Iter);
		Iter++;
	}*/
}
