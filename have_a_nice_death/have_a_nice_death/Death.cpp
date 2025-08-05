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

	UpdateState(Super::GetController()->GetInput());
	//TODO
	//�� ������Ʈ ����, �Է� ���� �޾Ƽ� ���¸� ����, �׸��� ���¸� ������
	// Ȥ�� ���¸��� �ִϸ��̼� ���ǵ尡 �ٸ� ���� ����
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
	//�ִϸ��̼��� ������ ���� ó��
	//[���� �ִ� �ִϸ��̼��̿���. -> Ideal]
	// [���߿� �ִ� ���¿���. -> falling]

	//���� ���
	//if(isground)
	{
		//���� �ִϸ��̼��� UTURN�� ���
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
	//�ִϸ������� ���¿�, �Է°��� ���� SetState�� ȣ��

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

		////���� ���� ���߿�, �ݴ� �Է��� ���� ��
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

		//�޸� �غ�
		if (state == EDeathStatepriority::State_Idle ||
			state == EDeathStatepriority::State_RunToIdle ||
			state == EDeathStatepriority::State_IdleUTurn)
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
			renderingFlipOrder = (movedir == -1) ? true : false;
			forwordDirection = movedir;

			animator.ResetAnimTimer();
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Dash), false);
			state = EDeathStatepriority::State_Dash;
			animator.SetAnimSpeed(10);
		}
	}

	//����
	else if (Input == KeyType::Z)
	{
		//���ݵ� ��� ��ȯ
		int32 movedir = InputManager::GetInstance()->GetMovePressedX();

		renderingFlipOrder = (movedir == -1) ? true : false;
		forwordDirection = movedir;

		animator.ResetAnimTimer();
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack1), false);
		state = EDeathStatepriority::State_Attack1;
		animator.SetAnimSpeed(35);



	}

	animator;
}
