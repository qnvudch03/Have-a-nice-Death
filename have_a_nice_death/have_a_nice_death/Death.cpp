#include "pch.h"
#include "Death.h"

void Death::Init()
{
	Super::Init();
	SetState("Ideal");
}

void Death::Update(float deltaTime)
{
	Super::Update(deltaTime);
	//TODO
	//�� ������Ʈ ����, �Է� ���� �޾Ƽ� ���¸� ����, �׸��� ���¸� ������
	// Ȥ�� ���¸��� �ִϸ��̼� ���ǵ尡 �ٸ� ���� ����
	//animaotr.SetAnimSpeed(30);
	//SetState("Ideal");
}

void Death::Destroy()
{
}
