#pragma once

class Object;

class Collider
{
public:
	///Ideal 상태에서의 사이즈를 넘겨받는다.
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

