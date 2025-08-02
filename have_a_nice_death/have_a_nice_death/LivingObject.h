#pragma once
#include "Object.h"

class Controller;

class LivingObject : public Object
{
	//�� �����͸� �޾Ƽ�, ���¿� ���� ��Ȳ�� �´� texture�� Object�� setTexture�� ȣ���ؼ� �����ϼ���.
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	void SetState(std::string state);
	LivingObject(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft) : Super(RenderType, anchorPosition)
	{
		_ownTextures = OwningTextures;
	}

	virtual ~LivingObject()
	{

	}

private:

	std::unordered_map<std::string, std::vector<Texture*>>* _ownTextures = nullptr;

	Controller* _controller = nullptr;
};

