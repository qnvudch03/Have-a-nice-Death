#pragma once
#include "Object.h"

class LivingObject : public Object
{
	//맵 데이터를 받아서, 상태에 따라 상황에 맞는 texture를 Object의 setTexture를 호출해서 설정하세요.
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	void SetState(std::string state);
	LivingObject(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, DrawAnchor anchorPosition = DrawAnchor::Topleft) : Super(RenderType, anchorPosition)
	{
		_ownTextures = OwningTextures;
	}

	virtual ~LivingObject()
	{

	}

private:
	std::vector<Texture*>* _Playtures = nullptr;
	std::unordered_map<std::string, std::vector<Texture*>>* _ownTextures = nullptr;
};

