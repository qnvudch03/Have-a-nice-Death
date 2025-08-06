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
	//TODO
	//매 업데이트 마다, 입력 값을 받아서 상태를 갱신, 그리고 상태를 보내줌
	// 혹시 상태마다 애니메이션 스피드가 다를 수도 있음
	//animaotr.SetAnimSpeed(30);
	//SetState("Ideal");

	SetPos(Vector(500, 300));
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
		}

		else if (state == EDeathStatepriority::State_Dash)
		{
			/*SetState(ConvertDeathStateToString(EDeathStatepriority::State_RunToIdle), false);
			state = EDeathStatepriority::State_RunToIdle;
			animator.SetAnimSpeed(15);

			return;*/
		}

		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Idle), true);
		state = EDeathStatepriority::State_Idle;
		animator.onPlay = true;
		animator.ResetAnimTimer();
	}




}

void Death::UpdateState(KeyType Input)
{
	//애니메이터의 상태와, 입력값에 따라 SetState를 호출

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

		////돌아 가는 도중에, 반대 입력이 들어올 때
		//if (state == EDeathStatepriority::State_IdleUTurn)
		//{
		//	if (forwordDirection != InputManager::GetInstance()->GetMoveDownX())
		//	{
		//		SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleUTurn), false);
		//		state = EDeathStatepriority::State_IdleUTurn;
		//		animator.SetAnimSpeed(10);

		//		return;
		//	}
		//}

		//달릴 준비
		if (state == EDeathStatepriority::State_Idle ||
			state == EDeathStatepriority::State_RunToIdle ||
			state == EDeathStatepriority::State_IdleUTurn)
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
			

			animator.ResetAnimTimer();
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Dash), false);
			state = EDeathStatepriority::State_Dash;
			animator.SetAnimSpeed(10);
		}

		//공격 모션 중, 대쉬로 캔슬로인한 콤보 초기화
		if (atkcombo != 0)
			atkcombo = 0;
	}

	//공격
	else if (Input == KeyType::Z)
	{

		if (state <= State_Dash)
			return;

		if (!Attack())
		{
			
		}

	}

	animator;
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
		animator.AnimTextureIndex < animator.TextureNum - 1 &&
		animator.AnimTextureIndex > 2)
	{

		LookDir();

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack3), false);
		state = EDeathStatepriority::State_Attack3;
		animator.SetAnimSpeed(20);

		atkcombo++;

		return true;
	}

	//4단
	else if (atkcombo == 3 &&
		state == EDeathStatepriority::State_Attack3 &&
		animator.AnimTextureIndex > 2)
	{
		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack4), false);
		state = EDeathStatepriority::State_Attack4;
		animator.SetAnimSpeed(20);

		atkcombo++;

		return true;
	}

	return false;
}
