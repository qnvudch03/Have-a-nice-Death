#include "pch.h"
#include "Animaotr.h"

void Animator::Update(float deltaTime)
{
	/*if (onPlay == false || TextureNum == 1)
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

	if (isAttackAnim && (hitboxIndex == AnimTextureIndex) )
	{
		onHitBoxSpawn();
	}*/

    if (onPlay == false || TextureNum == 1)
        return;


    if (_isReverse)
        _animStackTimer -= deltaTime * _animSpeed;
    else
        _animStackTimer += deltaTime * _animSpeed;

    
    if (_IsLoop)
    {
        if (_isReverse && _animStackTimer < 0)
            _animStackTimer = TextureNum - 1;
        else if (!_isReverse && _animStackTimer >= TextureNum)
            _animStackTimer = 0;
    }
    

    else
    {
        if (_isReverse && _animStackTimer < 0)
        {
            onPlay = false;
            _animStackTimer = 0;

            if(onAnimEnd != nullptr)
                onAnimEnd();
        }
        else if (!_isReverse && _animStackTimer > TextureNum - 1)
        {
            onPlay = false;
            _animStackTimer = TextureNum - 1;
            
            if (onAnimEnd != nullptr)
                onAnimEnd();
        }
    }

    AnimTextureIndex = (int32)_animStackTimer;

    if (isAttackAnim && (hitboxIndex == AnimTextureIndex) && hitboxIndex != -1)
    {
        if (onHitBoxSpawn != nullptr)
            onHitBoxSpawn();

        hitboxIndex = -1;
    }

    if (!hitboxIndexes.empty())
    {
        if (isAttackAnim && (hitboxIndexes.front() == AnimTextureIndex))
        {
            if (onHitBoxSpawn != nullptr)
                onHitBoxSpawn();

            hitboxIndexes.pop();
        }
    }

    
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
