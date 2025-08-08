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
	//�ִϸ��̼��� ������ ���� ó��
	//[���� �ִ� �ִϸ��̼��̿���. -> Ideal]
	// [���߿� �ִ� ���¿���. -> falling]

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

	//���� ���
	//if(isground)
	{
		//���� �ִϸ��̼��� ���� �� ���
		if (state == EDeathStatepriority::State_Attack1 ||
			state == EDeathStatepriority::State_Attack2 ||
			state == EDeathStatepriority::State_Attack3 ||
			state == EDeathStatepriority::State_Attack4)
		{
			atkcombo = 0;
		}


		//���� �ִϸ��̼��� UTURN�� ���
		if (state == EDeathStatepriority::State_IdleUTurn ||
			state == EDeathStatepriority::State_RunToUturn)
		{
			forwordDirection *= -1;
			renderingFlipOrder = (forwordDirection == -1) ? true : false;

			if (InputManager::GetInstance()->GetMovePressedX() != 0)
			{
				//ȸ�� �� �ٸ� ��ư�� ���� ����� ó��
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

	//�̵���ư ����
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

	//���� �� ��
	else if (Input == KeyType::StartMove)
	{
		//�޸��� ���߿� �ݴ� �Է��� ���� ��
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

		//�޸� �غ�
		if (state == EDeathStatepriority::State_Idle ||
			state == EDeathStatepriority::State_RunToIdle)// ||
			//state == EDeathStatepriority::State_IdleUTurn)
		{
			//�ٶ󺸴� ����� �Է� ������ �ٸ� ��
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

		//�������� ��
		if (state == EDeathStatepriority::State_JumptoFall)
		{
			int32 movedir = InputManager::GetInstance()->GetMoveDownX();

			if (movedir != 0)
				forwordDirection = movedir;

			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
		}

	}

	//�޸��� �ִ� ��
	else if (Input == KeyType::Move)
	{

		if (state > EDeathStatepriority::State_Attack4)
		{
			if (state == EDeathStatepriority::State_Running ||
				state == EDeathStatepriority::State_IdleToRun ||
				state == EDeathStatepriority::State_IdleUTurn ||
				state == EDeathStatepriority::State_RunToUturn)

				return;

			//���� �Է¹���� �ӵ��� ������ �� �� ����


			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Running));
			state = EDeathStatepriority::State_Running;
			animator.SetAnimSpeed(10);

		}

	}

	//�뽬
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

		//���� ��� ��, �뽬�� ĵ�������� �޺� �ʱ�ȭ
		if (atkcombo != 0)
			atkcombo = 0;
	}

	//����
	else if (Input == KeyType::Z)
	{

		if (state <= State_Hitted)
			return;

		if (!Attack())
		{
			
		}
	}

	//����
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

	//�뽬 ��� ����ó��
	if (DashException())
	{
		atkcombo = 0;
	}
	

	//1��
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

	//2��
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

	//3��
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

	//4��
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
