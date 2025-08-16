#include "pch.h"
#include "Death.h"
#include "Texture.h"
#include "Controller.h"
#include "HitBox.h"
#include "Game.h"
#include "GameScene.h"
#include "HitBoxManager.h"
#include "DebugLenderer.h"
#include "LivingObject.h"
#include "TimeManager.h"
#include "Elevator.h"

void Death::Init()
{
	Super::Init();

	SetState("Appear", false);
	state = EDeathStatepriority::State_Apear;
	animator.StopAnim();
	SETTRIPLE(false)

	isEffectGravity = false;

	//ü �ִ�ü�� �� �� ������Ÿ��, ���ݻ�Ÿ�, �̵��ӵ�, �����Ŀ�
	SetStat(ObjectStat(100, 100, 20, 5, 0, 30, 10, 500));

	CallElevator();
}

void Death::OnDeathSpawn()
{
	SetState("Appear", false);
	state = EDeathStatepriority::State_Apear;
	animator.StartAnim();
	animator.SetAnimSpeed(30);
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
	if (state == EDeathStatepriority::State_Apear)
	{
		SETTRIPLE(true)
		isEffectGravity = true;
	}

	if (!IsActive)
	{
		Die();
	}

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

			if (GetController()->GetInputPressedX() != 0)
			{
				//ȸ�� �� �ٸ� ��ư�� ���� ����� ó��
				int dir = GetController()->GetInputPressedX();
				if (forwordDirection != dir)
				{
					forwordDirection = dir;
					renderingFlipOrder = (forwordDirection == -1) ? true : false;
				}
			}

			if (state == EDeathStatepriority::State_IdleUTurn)
			{
				if (GetController()->GetInput() == KeyType::Left ||
					GetController()->GetInput() == KeyType::Right)
				{
					animator.onPlay = true;
					animator.ResetAnimTimer(10);

					SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleToRun), false);
					state = EDeathStatepriority::State_IdleToRun;
					LookInputDir();

					return;
				}
			}

		}

		//�뽬 ���� ��
		else if (state == EDeathStatepriority::State_Dash)
		{
			LookInputDir();
			isEffectGravity = true;
		}

		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Idle), true);
		state = EDeathStatepriority::State_Idle;
		animator.onPlay = true;
		animator.ResetAnimTimer();
		LookInputDir();

		DamagedAble = true;
	}

}

void Death::OnHitBoxSpawn()
{

	HitBoxManager* hitBoxManager = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence())->GetHitBoxManager();
	HitBox* hitbox = hitBoxManager->CallHitBox();

	Vector colliderCenterPos = collider->GetCenterPos();
	Vector hitBoxSize = { 0,0 };

	switch (state)
	{
	case Death::State_Attack1:
		colliderCenterPos.x += 150 * forwordDirection;
		colliderCenterPos.y += 20;
		hitBoxSize.x = 100;
		hitBoxSize.y = 40;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.1, GetController()->isPlayerController, this);
		break;
	case Death::State_Attack2:
		colliderCenterPos.y -= 45;

		hitBoxSize.x = 120;
		hitBoxSize.y = 110;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.1, GetController()->isPlayerController, this);
		break;
	case Death::State_Attack3:
		colliderCenterPos.y -= 85;

		hitBoxSize.x = 180;
		hitBoxSize.y = 150;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk, HitBoxType::Fixed, 0.1, GetController()->isPlayerController, this);
		break;
	case Death::State_Attack4:
		colliderCenterPos.x += 175 * forwordDirection;
		colliderCenterPos.y -= 125;

		hitBoxSize.x = 100;
		hitBoxSize.y = 190;

		hitbox->SetHitBox(colliderCenterPos, hitBoxSize, GetStat().atk * 1.3, HitBoxType::Fixed, 0.3, GetController()->isPlayerController, this);
		break;

	default:
		break;
	}

	hitBoxManager->AddHitBox(hitbox);

	Game::GetInstance()->GetDebugLenderer()->ReservedHitBox(hitbox);
}

void Death::Hitted(HitBox* hitbox)
{
	if (!DamagedAble)
		return;

	Super::Hitted(hitbox);

}

void Death::UpdateState(KeyType Input)
{
	if (!IsActive)
		return;


	//��� ��� üũ ����
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

		if (state == EDeathStatepriority::State_Dash || 
			state == EDeathStatepriority::State_Hitted ||
			state == EDeathStatepriority::State_Death ||
			state == EDeathStatepriority::State_Apear)
		{
			DamagedAble = false;
		}

		else
		{
			DamagedAble = true;
		}
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
	else if (Input == KeyType::Right ||
		Input == KeyType::Left)
	{
		//�޸��� ���߿� �ݴ� �Է��� ���� ��
		if (state == EDeathStatepriority::State_Running)
		{
			if (forwordDirection != GetController()->GetInputDownX())
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
			if (forwordDirection != GetController()->GetInputDownX())
			{
				SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleUTurn), false);
				state = EDeathStatepriority::State_IdleUTurn;
				animator.SetAnimSpeed(15);
			}

			else
			{
				SetState(ConvertDeathStateToString(EDeathStatepriority::State_IdleToRun), false);
				state = EDeathStatepriority::State_IdleToRun;
				animator.SetAnimSpeed(15);
			}


		}

		//�������� ��
		if (state == EDeathStatepriority::State_JumptoFall ||
			state == EDeathStatepriority::State_JumpStart)
		{
			int32 movedir = GetController()->GetInputDownX();

			if (movedir != 0)
				forwordDirection = movedir;

			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
		}

	}

	//�޸��� �ִ� ��
	else if (Input == KeyType::KeepLeft ||
			Input == KeyType::KeepRight)
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
		int32 movedir = CheckDashCondition();

		if (movedir == 0)
			return;

		if (state > EDeathStatepriority::State_Dash)
		{
			if (movedir != 0)
				forwordDirection = movedir;

			renderingFlipOrder = (movedir == -1) ? true : (movedir == 1) ? false : renderingFlipOrder;
			
			if (!wallSensor->IsActive())
			{
				velocity = Vector(forwordDirection * 10, 0);
			}
			
			animator.ResetAnimTimer();
			SetState(ConvertDeathStateToString(EDeathStatepriority::State_Dash), false);
			state = EDeathStatepriority::State_Dash;
			animator.SetAnimSpeed(10);

			isEffectGravity = false;

			DamagedAble = false;
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

		if (Attack())
		{
			//���� ��� ��, x �ӵ��� ������
			velocity.x *= 0.7;
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

void Death::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	if (IsActive)
	{
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Hitted), false);
		state = EDeathStatepriority::State_Hitted;

		atkcombo = 0;
	}
}

bool Death::Attack()
{

	auto LookDir = [this]()
		{
			int32 movedir = GetController()->GetPastInputPressedX();

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
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack1), false, 2); //ù���� ������ 0 �Դϴ�.
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
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack2), false, 1);
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
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack3), false, 1);
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
		SetState(ConvertDeathStateToString(EDeathStatepriority::State_Attack4), false, 10);
		state = EDeathStatepriority::State_Attack4;
		animator.SetAnimSpeed(20);

		atkcombo++;

		return true;
	}

	return false;
}

int Death::CheckDashCondition()
{
	KeyType pastInput = GetController()->GetPastInput();

	if (pastInput == KeyType::KeepRight ||
		pastInput == KeyType::Right)
	{
		return 1;
	}

	if (pastInput == KeyType::KeepLeft ||
		pastInput == KeyType::Left)
	{
		return -1;
	}

	return 0;
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
	KeyType currentInput = GetController()->GetInput();
	int32 movedir = 0;

	if (currentInput == KeyType::Right ||
		currentInput == KeyType::KeepRight)
	{
		movedir = 1;
	}

	else if (currentInput == KeyType::Left ||
		currentInput == KeyType::KeepLeft)
	{
		movedir = -1;
	}

	

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

void Death::CallElevator()
{
	Vector elevatorPosition = GetPos();
	elevatorPosition.x -= 0;
	elevatorPosition.y += 10;

	Elevator* elevator = new Elevator(SpriteManager::GetInstance()->GetTextures("Elevator", "open"), RenderLayer::Platform, elevatorPosition, ImageAnchor::Bottomcenter);

	elevator->animator.onAnimEnd = [this, elevator]() {

		elevator->callCount++;

		if (elevator->callCount == 1)
		{
			OnDeathSpawn();
			//elevator->SetAnimaotrTextures(SpriteManager::GetInstance()->GetTextures("Elevator", "close"), false);
			elevator->animator.SetReversePlay();
			elevator->animator.StartAnim();
		}

		else if (elevator->callCount == 2)
		{
			Game::GetInstance()->GetGameScene()->EraseFromGame(elevator);
		}
	};

	Game::GetInstance()->GetGameScene()->LoadObject(elevator);
}
