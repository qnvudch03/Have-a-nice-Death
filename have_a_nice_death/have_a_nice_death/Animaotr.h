#pragma once
#include "Texture.h"

class Animaotr
{
public:

	//void Destory() { delete _animtures; }

	int32 AnimTextureIndex = 0;
	int32 TextureNum = 0;

	void SetAnimSpeed(int32 speed) { _animSpeed = speed; }
	void SetAnimTexture(std::vector<Texture*>* animtures) { _animtures = animtures; }

	void Update(float deltaTime);

	Texture* GetAnimTexture()
	{
		return (*_animtures)[AnimTextureIndex];
	}

private:
	int32 _animSpeed = 0;
	float _animStackTimer = 0;
	std::vector<Texture*>* _animtures = nullptr;
};

