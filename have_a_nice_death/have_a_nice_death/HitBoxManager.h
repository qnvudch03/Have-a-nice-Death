#pragma once

#include "HitBox.h"

class HitBoxManager
{
public:
	HitBoxManager(){}
	~HitBoxManager();

	void Init();

	HitBox* CallHitBox();
	void AddHitBox(HitBox* hitbox)
	{
		spanwedHitBoxVec.insert(hitbox);
	}
	void ReturnHitBox(HitBox* hitbox);
	void Update(float deltatime);

private:
	std::queue<HitBox*> hitBoxPull;
	std::set<HitBox*> spanwedHitBoxVec;
	//std::vector<HitBox*> spanwedHitBoxVec;
};

