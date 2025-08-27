#pragma once
#include "Controller.h"
class AIController : public Controller
{
	enum AIInputList
	{
		AI_InputLeft,
		AI_InputRight,
		AI_InputJump,
		AI_InputAttack,
		AI_InputDash,
		AI_InputMax
	};

	enum AIState {
		AI_Patrol,
		AI_Chase,
		AI_Attack,
	};

public:

	AIController();

	virtual void Update(float deltatime) override;
private:

	LivingObject*& target;

	float inputTimer = 0.0f;      
	float inputDuration = 5.0f;   
	float coolTimer = 0.0f;       
	float coolDuration = 2.0f;    

	bool isInCoolTime = false;    


	int stack_counter = 10;
	int input_Interver = stack_counter;
};

