#pragma once

class Object;

class Collider
{
public:
	///Ideal ���¿����� ����� �Ѱܹ޴´�.
	Collider(Object* Owner, Vector Size) : owner(Owner), size(Size) {}
	~Collider() = default;

	void DeActivateCollier();
	void ActivateCollier();

	RectanglePos Getrectangle() { return rectangle; }

	void Update();
	void InitPos();

	Vector GetSize() { return size; }
	Vector GetCenterPos(){ return colliderCenterPos; }

	bool CheckIsActive() { return isActivated; }

private:
	Vector pos;
	Vector size;
	Object* owner = nullptr;

	Vector colliderCenterPos;

	RectanglePos rectangle;

	bool isActivated = true;
};

