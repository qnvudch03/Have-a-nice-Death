#pragma once
#include "Texture.h"

class Animator
{
public:

	//void Destory() { delete _animtures; }

	int32 AnimTextureIndex = 0;
	int32 TextureNum = 0;

	void SetAnimSpeed(int32 speed) { _animSpeed = speed; }
	void SetAnimTexture(std::vector<Texture*>* animtures) { _animTextures = animtures; }

	void Destroy();

	void Update(float deltaTime);

	Texture* GetAnimTexture()
	{
		return (*_animTextures)[AnimTextureIndex];
	}

private:
	int32 _animSpeed = 0;
	float _animStackTimer = 0;
	std::vector<Texture*>* _animTextures = nullptr;
};

