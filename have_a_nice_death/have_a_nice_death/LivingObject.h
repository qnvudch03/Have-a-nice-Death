#pragma once
#include "Object.h"
#include "Sensor.h"
#include "Collider.h"

class Sensor;

class Controller;

class LivingObject : public Object
{

	struct ObjectStat
	{
		int hp = 10;
		int atk = 10;
		int def = 5;
		float attack_duration = 0;
		float attack_range = 0;
		float moveForce = 10;
		float jumpPower = 500;

	};

	ObjectStat GetStat() { return objectStat; }

	//맵 데이터를 받아서, 상태에 따라 상황에 맞는 texture를 Object의 setTexture를 호출해서 설정하세요.
	using Super = Object;

public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void SetDebugMode(bool debugmode) override;
	virtual void SetCollider() override;

	void SetState(std::string state, bool IsLoop = true, int32 atkIndex = -1);
	void SetController(Controller* controller) { _controller = controller; }

	void ApplyEnvironment(float detaTime);

	bool checkCollision(LivingObject* object, Vector start, Vector end);

	//Movecorner
	int forwordDirection = 1;

	bool isCanMove = true;
	bool isCanJump = false;
	bool isTurning = false;
	bool isEffectGravity = true;

	Vector velocity;
	Vector acceleration;
	float gravityPower = 9.8;

	bool isGround = false;

	Vector AddForce(Vector dir, float Power);


	Controller* GetController() { return _controller; }

	LivingObject(std::unordered_map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft) : Super(RenderType, anchorPosition)
	{
		animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
		animator.onHitBoxSpawn = [this]() {this->OnHitBoxSpawn(); };
		ownTextures = OwningTextures;

		SetCollider();

		//쎈서 할당
		{
			Vector objPos = GetPos();
			Vector size = collider->GetSize();
			groundSensor = new Sensor(this, Vector(50, 20), SensorType::GroundSensor);
			wallSensor = new Sensor(this, Vector(20, 100), SensorType::WallSensor);
			cornerSensor = new Sensor(this, Vector(50, 20), SensorType::CornerSensor);
		}
	}

	virtual ~LivingObject()
	{
		for (auto sensor : SensorArray)
		{
			delete *sensor;
		}
	}

	virtual void OnAnimEnd() {}
	virtual void OnHitBoxSpawn() {}

	//감지 센서들
	Sensor* groundSensor = nullptr;
	Sensor* wallSensor = nullptr;
	Sensor* cornerSensor = nullptr;

private:

	std::unordered_map<std::string, std::vector<Texture*>>* ownTextures = nullptr;

	Controller* _controller = nullptr;

	ObjectStat objectStat;

	Sensor** SensorArray[3] = { &groundSensor , &wallSensor, &cornerSensor };
};

