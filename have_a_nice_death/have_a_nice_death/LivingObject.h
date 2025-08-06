#pragma once
#include "Object.h"

class Controller;

class LivingObject : public Object
{

	struct ObjectStat
	{
		int hp = 0;
		int atk = 0;
		int def = 0;
		float attack_duration = 0;
		float attack_range = 0;
		int speed = 0;
	};

	ObjectStat GetStat() { return objectStat; }

	//�� �����͸� �޾Ƽ�, ���¿� ���� ��Ȳ�� �´� texture�� Object�� setTexture�� ȣ���ؼ� �����ϼ���.
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void SetDebugMode(bool debugmode) override;

	void SetState(std::string state, bool IsLoop = true);
	void SetController(Controller* controller) { _controller = controller; }

	int forwordDirection = 1;

	Controller* GetController() { return _controller; }

	LivingObject(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft) : Super(RenderType, anchorPosition)
	{
		animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
		ownTextures = OwningTextures;
	}

	virtual ~LivingObject()
	{

	}

	virtual void OnAnimEnd() {}

private:

	std::unordered_map<std::string, std::vector<Texture*>>* ownTextures = nullptr;

	Controller* _controller = nullptr;

	ObjectStat objectStat;
};

