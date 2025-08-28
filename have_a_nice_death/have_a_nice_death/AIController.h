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
		AI_Default
	};

public:

	AIController();

	virtual void Update(float deltatime) override;
	LivingObject* GetTarget() { return *target; }

private:

	LivingObject** target;

	AIState state = AIState::AI_Default;
	void decideInput();
	int LookTarget();

	float patrolTimer = 0.0f;
	float patrolInterval = 1.5f;

	float attackTimer = 0.0f;
	float attackInterval = 2.5f;

	int moveDir = 0;

	float GetCombatEnterRange() const;
	KeyType ChooseAttackByDistance(float distX);

	//float inputTimer = 0.0f;      
	//float inputDuration = 5.0f;   
	//float coolTimer = 0.0f;       
	//float coolDuration = 2.0f;    

	//bool isInCoolTime = false;    


	//int stack_counter = 10;
	//int input_Interver = stack_counter;
};

