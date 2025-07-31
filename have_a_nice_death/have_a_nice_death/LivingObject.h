#pragma once
#include "Object.h"

class LivingObject : public Object
{
	//�� �����͸� �޾Ƽ�, ���¿� ���� ��Ȳ�� �´� texture�� Object�� setTexture�� ȣ���ؼ� �����ϼ���.
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	LivingObject(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, bool havetoDrawCenter = false) : Super(RenderType, havetoDrawCenter)
	{
		_ownTextures = OwningTextures;
	}

	~LivingObject()
	{

	}

private:
	std::vector<Texture*>* _Playtures = nullptr;
	std::unordered_map<std::string, std::vector<Texture*>>* _ownTextures = nullptr;
};

