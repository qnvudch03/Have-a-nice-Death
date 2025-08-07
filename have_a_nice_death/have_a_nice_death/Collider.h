#pragma once

class Object;

class Collider
{
public:
	///Ideal ���¿����� ����� �Ѱܹ޴´�.
	Collider(Object* Owner, Vector Size) : owner(Owner), size(Size) {}
	~Collider() = default;

	RectanglePos Getrectangle() { return rectangle; }

	void Update();
	void InitPos();

private:
	Vector pos;
	Vector size;
	Object* owner = nullptr;

	RectanglePos rectangle;
};

