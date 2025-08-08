#pragma once
#include "Texture.h"

class Animator
{
public:



	//void Destory() { delete _animtures; }

	int32 AnimTextureIndex = 0;
	int32 TextureNum = 0;
	bool onPlay = false;

	void SetAnimSpeed(int32 speed) { _animSpeed = speed; }
	void SetAnimTexture(std::vector<Texture*>* animtures, bool IsLoop) 
	{ 
		_animStackTimer = 0;
		_animTextures = animtures;
		_IsLoop = IsLoop; 
		AnimTextureIndex = 0;
		onPlay = true;
	}

	void ResetAnimTimer(float animSpeed = DefaultAnimSpeed) { _animStackTimer = 0;  _animSpeed = animSpeed; _IsLoop = true; }

	void Destroy();

	void Update(float deltaTime);

	std::function<void()> onAnimEnd;

	std::vector<Texture*>* GetAnimTextureVec() { return _animTextures; }

	Texture* GetAnimTexture()
	{
		if (_animTextures == nullptr)
			return nullptr;

		return (*_animTextures)[AnimTextureIndex];
	}

private:
	bool _IsLoop = true;
	int32 _animSpeed = 0;
	float _animStackTimer = 0;
	std::vector<Texture*>* _animTextures = nullptr;
};

