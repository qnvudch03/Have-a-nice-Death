#include "pch.h"
#include "Death.h"
#include "Texture.h"
#include "Controller.h"

void Death::Init()
{
	Super::Init();

	SetState("Ideal");
}

void Death::Update(float deltaTime)
{
	Super::Update(deltaTime);

	deltatime = deltaTime;

	UpdateState(Super::GetController()->GetInput());

	isCanMove = IsCamMove(state);

	isCanJump = IsCanJump(state);
}

void Death::Destroy()
{
}

void Death::OnAnimEnd()
{
	//TODO
	//애니메이션이 끝났을 떄의 처리
	//[땅에 있는 애니메이션이였다. -> Ideal]
	// [공중에 있는 상태였다. -> falling]

	if (state == EDeathStatepriority::State_JumpStart)
	{
		if (!groundSensor->IsActive())
		{
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_JumptoFall), true);
			state = EDeathStatepriority::State_JumptoFall;
			animator.ResetAnimTimer(20);
			return;
		}
	}

	//땅일 경우
	//if(isground)
	{
		//종료 애니메이션이 공격 일 경우
		if (state == EDeathStatepriority::State_Attack1 ||
			state == EDeathStatepriority::State_Attack2 ||
			state == EDeathStatepriority::State_Attack3 ||
			state == EDeathStatepriority::State_Attack4)
		{
			atkcombo = 0;
		}


		//종료 애니메이션이 UTURN일 경우
		if (state == EDeathStatepriority::State_IdleUTurn ||
			state == EDeathStatepriority::State_RunToUturn)
		{
			forwordDirection *= -1;
			renderingFlipOrder = (forwordDirection == -1) ? true : false;

			if (InputManager::GetInstance()->GetMovePressedX() != 0)
			{
				//회전 중 다른 버튼을 누른 경우의 처리
				int dir = InputManager::GetInstance()->GetMovePressedX();
				if (forwordDirection != dir)
				{
					forwordDirection = dir;
					renderingFlipOrder = (forwordDirection == -1) ? true : false;
				}
			}

		}

		else if (state == EDeathStatepriority::State_Dash)
		{
			LookInputDir();
			isEffectGravity = true;
		}

		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Idle), true);
		state = EDeathStatepriority::State_Idle;
		animator.onPlay = true;
		animator.ResetAnimTimer();
	}




}

void Death::UpdateState(KeyType Input)
{
	if (state == EDeathStatepriority::State_JumptoFall &&
		groundSensor->IsActive())
	{
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_JumptoLand), false);
		state = EDeathStatepriority::State_JumptoLand;
		animator.SetAnimSpeed(10);

		velocity.x *= 0.25;
	}


	if (state == EDeathStatepriority::State_RunToUturn ||
		state == EDeathStatepriority::State_IdleUTurn)
	{
		isTurning = true;
		velocity.x *= 0.8;
	}

	else
	{
		isTurning = false;
	}

	//이동버튼 해제
	if (Input == KeyType::RELEASE)
	{
		if (state == EDeathStatepriority::State_Running ||
			state == EDeathStatepriority::State_IdleToRun)
		{
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_RunToIdle), false);
			state = EDeathStatepriority::State_RunToIdle;
			animator.SetAnimSpeed(15);
		}
	}

	//움직 일 때
	else if (Input == KeyType::StartMove)
	{
		//달리는 도중에 반대 입력이 들어올 때
		if (state == EDeathStatepriority::State_Running)
		{
			if (forwordDirection != InputManager::GetInstance()->GetMoveDownX())
			{
				SetState(ConvertDeathStateToString(EDeathStatepriority::State_RunToUturn), false);
				state = EDeathStatepriority::State_RunToUturn;
				animator.SetAnimSpeed(10);

				return;
			}
		}

		//달릴 준비
		if (state == EDeathStatepriority::State_Idle ||
			state == EDeathStatepriority::State_RunToIdle)// ||
			//state == EDeathStatepriority::State_IdleUTurn)
		{
			//바라보는 방향과 입력 방향이 다를 떄
			if (forwordDirection != InputManager::GetInstance()->GetMoveDownX())
			{
				SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleUTurn), false);
				state = EDeathStatepriority::State_IdleUTurn;
				animator.SetAnimSpeed(10);
			}

			else
			{
				SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleToRun), false);
				state = EDeathStatepriority::State_IdleToRun;
				animator.SetAnimSpeed(15);
			}


		}

		//떨어지는 중
		if (state == EDeathStatepriority::State_JumptoFall)
		{
			int32 movedir = InputManager::GetInstance()->GetMoveDownX();

			if (movedir != 0)
				forwordDirection = movedir;

			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
		}

	}

	//달리고 있는 중
	else if (Input == KeyType::Move)
	{

		if (state > EDeathStatepriority::State_Attack4)
		{
			if (state == EDeathStatepriority::State_Running ||
				state == EDeathStatepriority::State_IdleToRun ||
				state == EDeathStatepriority::State_IdleUTurn ||
				state == EDeathStatepriority::State_RunToUturn)

				return;

			//현재 입력방향과 속도가 같은지 비교 후 조정


			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Running));
			state = EDeathStatepriority::State_Running;
			animator.SetAnimSpeed(10);

		}

	}

	//대쉬
	else if (Input == KeyType::Shift)
	{
		int32 movedir = InputManager::GetInstance()->GetMovePressedX();

		if (movedir == 0)
			return;

		if (state > EDeathStatepriority::State_Dash)
		{
			if (movedir != 0)
				forwordDirection = movedir;

			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
			
			velocity = Vector(forwordDirection * 10, 0);
			animator.ResetAnimTimer();
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Dash), false);
			state = EDeathStatepriority::State_Dash;
			animator.SetAnimSpeed(10);

			isEffectGravity = false;
		}

		//공격 모션 중, 대쉬로 캔슬로인한 콤보 초기화
		if (atkcombo != 0)
			atkcombo = 0;
	}

	//공격
	else if (Input == KeyType::Z)
	{

		if (state <= State_Hitted)
			return;

		if (!Attack())
		{
			
		}
	}

	//점프
	else if (Input == KeyType::SpaceBar)
	{
		DashException();

		if (state <= State_JumpStart)
			return;

		if (!groundSensor->IsActive())
			return;

		LookInputDir();

		atkcombo = 0;
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_JumpStart), false);
		state = EDeathStatepriority::State_JumpStart;
		animator.SetAnimSpeed(20);

	}
}

bool Death::Attack()
{

	auto LookDir = [this]()
		{
			int32 movedir = InputManager::GetInstance()->GetMovePressedX();

			if(movedir !=0)
				forwordDirection = movedir;
			
			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
		};

	//대쉬 모션 예외처리
	if (DashException())
	{
		atkcombo = 0;
	}
	

	//1단
	if (atkcombo == 0 &&
		state > EDeathStatepriority::State_Dash &&
		state != EDeathStatepriority::State_Attack1)
	{
		LookDir();

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack1), false);
		state = EDeathStatepriority::State_Attack1;
		animator.SetAnimSpeed(20);
		atkcombo++;

		return true;
	}

	//2단
	else if (atkcombo == 1 &&
		state == EDeathStatepriority::State_Attack1 &&
		animator.AnimTextureIndex < animator.TextureNum - 1 &&
		animator.AnimTextureIndex > 3)
	{

		LookDir();

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack2), false);
		state = EDeathStatepriority::State_Attack2;
		animator.SetAnimSpeed(20);

		atkcombo++;

		return true;
	}

	//3단
	else if (atkcombo == 2 &&
		state == EDeathStatepriority::State_Attack2 &&
		animator.AnimTextureIndex <= animator.TextureNum &&
		animator.AnimTextureIndex > 1)
	{

		LookDir();

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack3), false);
		state = EDeathStatepriority::State_Attack3;
		animator.SetAnimSpeed(10);

		atkcombo++;

		return true;
	}

	//4단
	else if (atkcombo == 3 &&
		state == EDeathStatepriority::State_Attack3 &&
		animator.AnimTextureIndex > 2)
	{
		LookDir();

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack4), false);
		state = EDeathStatepriority::State_Attack4;
		animator.SetAnimSpeed(20);

		atkcombo++;

		return true;
	}

	return false;
}

bool Death::DashException()
{
	if (state == EDeathStatepriority::State_Dash && animator.AnimTextureIndex >= animator.TextureNum - 3)
	{
		state = EDeathStatepriority::State_Idle;
		isEffectGravity = true;
		return true;
	}
	return false;
}

void Death::LookInputDir()
{
	int32 movedir = InputManager::GetInstance()->GetMovePressedX();

	if (movedir != 0)
		forwordDirection = movedir;

	renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
}

bool Death::IsCanJump(EDeathStatepriority state)
{
	if (state <= State_Hitted &&
		state == State_JumptoLand &&
		state == State_JumptoFall &&
		state == State_JumpStart
		)
		return false;

	else
		return true;
}
