#pragma once
#include "Object.h"
#include "Sensor.h"
#include "Collider.h"
#include "Book.h"
#include "HitBox.h"
#include "InputManager.h"

#define SETTRIPLE(x) isCanMove = x; isCanJump = x; DamagedAble = x;

class Sensor;

class Controller;



class LivingObject : public Object
{
	//맵 데이터를 받아서, 상태에 따라 상황에 맞는 texture를 Object의 setTexture를 호출해서 설정하세요.
	using Super = Object;


public:

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	virtual void SetDebugMode(bool debugmode) override;
	virtual void SetCollider() override;

	virtual void UpdateState(KeyType Input) {}

	void SetSingleCallbackState(std::string state, bool IsLoop = true, int32 atkIndex = -1);
	void SetMultiCallBackState(std::string state, bool IsLoop = true, std::vector<int32> atkIndexs = {});
	void SetController(Controller* controller) { _controller = controller; }

	void Die();
	std::function<void(LivingObject* deadCharacter)> OnDie;

	void LookInputDir();

	void ApplyEnvironment(float detaTime);
	void AddAcceleration(Vector power)
	{
		acceleration + power;
	}

	ObjectStat GetStat() { return objectStat; }
	void SetStat(ObjectStat stat) { objectStat = stat; }
	void AddStatByIndex(int index, float amount);
	void SetStatByIndex(int index, float amount);

	//bool checkCollision(LivingObject* object, Vector start, Vector end);

	//Movement
	int forwordDirection = 1;

	bool isCanMove = true;
	bool isCanJump = false;
	bool isTurning = false;
	bool isEffectGravity = true;

	float actionSpeed = 1.0;

	Vector velocity;
	Vector acceleration;
	float gravityPower = 50;

	bool isGround = false;
	virtual void OnLanded() {};

	void SetBook(Book* Book) { book = Book; }

	void AddForce(Vector dir, float Power);

	//Battle

	virtual void TakeDamage(float Damage);
	bool DamagedAble = true;
	virtual void Hitted(HitBox* hitbox);
	std::function<void()> OnHitted = nullptr;

	void SetDetectRnage(float rnage) { detectRange = rnage; }
	float GetDetectRange() { return detectRange; }

	//Active
	bool IsActive = true;

	//Anim
	bool IsessentialAnim = false;


	Controller* GetController() { return _controller; }

	LivingObject(std::map<std::string, std::vector<Texture*>>* OwningTextures, RenderLayer RenderType, ImageAnchor anchorPosition = ImageAnchor::Topleft) : Super(RenderType, anchorPosition)
	{
		animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
		animator.onHitBoxSpawn = [this]() {this->AnimCallBack(); };
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

		if (book != nullptr)
		{
			delete book;
		}
		
	}

	virtual void OnAnimEnd() {}
	virtual void AnimCallBack() {}

	//감지 센서들
	Sensor* groundSensor = nullptr;
	Sensor* wallSensor = nullptr;
	Sensor* cornerSensor = nullptr;

	std::vector<AttackSlot> AttackProfile;

private:

	std::map<std::string, std::vector<Texture*>>* ownTextures = nullptr;

	Controller* _controller = nullptr;

	Sensor** SensorArray[3] = { &groundSensor , &wallSensor, &cornerSensor };

	Book* book = nullptr;

	ObjectStat objectStat;

	void GenHitEffect();

	float detectRange = 0;

	//이펙트 기능
	//std::vector<Texture*>* EffectTexture = nullptr;
};

