#pragma once
#include "Texture.h"

class Animator
{
public:

	//void Destory() { delete _animtures; }

	std::queue<int32> hitboxIndexes;
	int32 hitboxIndex = -1;
	bool isAttackAnim = false;

	int32 AnimTextureIndex = 0;
	int32 TextureNum = 0;
	bool onPlay = false;

	void SetAnimSpeed(int32 speed) { _animSpeed = speed; }
	void SetAnimLoop(bool Isloop) { _IsLoop = Isloop; }
	void SetAnimTexture(std::vector<Texture*>* animtures, bool IsLoop, bool IsAttackAnim = false, int32 HitBoxIndex = -1)
	{ 
		ClearHitBosQueue();

		_animStackTimer = 0;
		_animTextures = animtures;
		_IsLoop = IsLoop; 
		AnimTextureIndex = 0;
		onPlay = true;
		isAttackAnim = IsAttackAnim;
		hitboxIndex = HitBoxIndex;

		//hitboxIndexes.push(HitBoxIndex);
	}

	void SetMultiAnimTexture(std::vector<Texture*>* animtures, bool IsLoop, bool IsAttackAnim = false, std::vector<int32> HitBoxIndexes = {})
	{
		ClearHitBosQueue();

		_animStackTimer = 0;
		_animTextures = animtures;
		_IsLoop = IsLoop;
		AnimTextureIndex = 0;
		onPlay = true;
		isAttackAnim = IsAttackAnim;
		hitboxIndex = -1;

		for (int i = 0; i < HitBoxIndexes.size(); i++)
		{
			hitboxIndexes.push(HitBoxIndexes[i]);
		}
	}

	void ResetAnimTimer(float animSpeed = DefaultAnimSpeed) { _animStackTimer = 0;  _animSpeed = animSpeed; _IsLoop = true; }

	void Destroy();

	void Update(float deltaTime);

	void StopAnim() { onPlay = false; }
	void StartAnim() { onPlay = true; }

	void SetReversePlay() { _isReverse = true; _animStackTimer = TextureNum - 1;}
	void SetCorrectPlay() { _isReverse = false; _animStackTimer = 0;}

	void ClearHitBosQueue()
	{
		while (!hitboxIndexes.empty())
			hitboxIndexes.pop();

	}

	std::function<void()> onAnimEnd = nullptr;
	std::function<void()> onHitBoxSpawn = nullptr;

	std::vector<Texture*>* GetAnimTextureVec() { return _animTextures; }

	Texture* GetAnimTexture()
	{
		if (_animTextures == nullptr)
			return nullptr;

		return (*_animTextures)[AnimTextureIndex];
	}

private:

	Vector atkBoxPos;

	bool _isReverse = false;
	bool _IsLoop = true;
	int32 _animSpeed = 0;
	float _animStackTimer = 0;
	std::vector<Texture*>* _animTextures = nullptr;
};

