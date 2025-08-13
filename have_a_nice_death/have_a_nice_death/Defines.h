#pragma once

//  �츮�� �����ϴ� ���� �����.
const int32 GWinSizeX = 1700;
const int32 GWinSizeY = 800;

#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

float RadianToDegree(float radian);
float DegreeToRadian(float degree);
bool IsInPoint(RECT rect, POINT pos);

// �𸮾󿡼� ������.
#define SMALL_NUMBER			(1.e-8f)
#define DefaultAnimSpeed 30


//////////////////GameEnum
enum UiType
{
	Image,
	Button,
	UiDefault
};

enum RenderLayer
{
	Background,
	Platform,
	Character,
	Effect,
	Max
};

enum ImageAnchor
{
	Topleft,
	Center,
	Bottomright,
	Bottomcenter,
	Positiondefault
};

enum SensorType
{
	WallSensor,
	GroundSensor,
	CornerSensor,
	SensorMax
};

enum HitBoxType
{
	Fixed,
	Movable,
	Default_HitBox
};


//////////////////



//////////////////GameStruct
struct SpriteInfo
{
	int32 startX = 0;
	int32 startY = 0;
	float dur = 0;
	bool loop = false;
	std::string textureKey;
};

struct Size
{
	int32 Width = 0;
	int32 Height = 0;
};

// vector ���� ((����+ũ��)�� ��Ÿ���� ����)
struct Vector
{
	// ��ǥ
	float x = 0;
	float y = 0;

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	//Vector p1;
	//Vector p2;
	//Vector p3 = Vector(p1.x + p2.x, p1.y + p2.y);
	//Vector p3 = p1 + p2;
	//p1 += p2;	// �̷� ������ �Ҽ� ��������
	//
	//int a = 10;
	//a += 1;

	// ��Ģ���� ����
	// +, - , *, / 
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	Vector operator*(float ratio)
	{
		Vector ret;
		ret.x = x * ratio;
		ret.y = y * ratio;
		return ret;
	}
	Vector operator*(Vector other)
	{
		Vector ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}
	bool operator==(const Vector& other) const
	{
		return (x == other.x && y == other.y);
	}
	// ���͸� ������������ ������ �ʴ�...
	// ������ �ȸ��� ������ ���Ǿ�����.


	// ������ ���� ���ϱ�
	// ���� ���캸��, Legnth, LengthSquared (���ʹ� ���� ���̸� �����ϴ� �Լ��� 2����)
	// sqrt(��Ʈ) ������ �������� ��α� ������, �� ��¥ ���̰� �ʿ��� ��찡 �ƴϸ�,
	// LengthSquared (���� ����) ������ ����ϴ°� �� ����.
	float Length()
	{
		return ::sqrt(x * x + y * y);
	}

	// ������ ���� ����
	float LengthSquared()
	{
		return (x * x + y * y);
	}

	// �̰͵� ���Ӹ���ٰ�. �پ��� ������ �ʿ��ϸ� ���⿡ ������ �ϸ� �ǿ�.
	void Normalize()
	{
		// ������ ��ֶ����� �ϴ� ������ ���������.
		// ������ ��ֶ����� ���� �ʰ�, �����ϴ� ������ �߰��� ������� �־��.
		
		// ������ ũ�⸦ ���ؼ�, ũ�⸸ŭ ������ ���ָ� �ȴ�.
		float length = Length();

		// �𸮾� ������ Ǯ ���¼ҽ�. �𸮾� �����ؼ� �����ص� �����ϴ�.
		//length �� 0�̰ų� ��û ������ �ִ�
		if (length < SMALL_NUMBER)
			return;	// ���� ����ȭ���ϰ� ����

		// ����ȭ.
		x /= length;
		y /= length;	
	}

	Vector GetNormalize()
	{
		Vector normalize = *this;
		normalize.Normalize();
		return normalize;
	}

	// ������ Dot 
	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// radian ������ŭ ȸ����Ű��.
	Vector Rotate(float radian)
	{
		float cosA = ::cosf(radian);
		float sinA = ::sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}

	// ������ Cross
	float Cross(const Vector& other)
	{
		//2D ��, ��Į�󰪸� ��ȯ�� �Ѵ�. 
		// ���� ���Ͱ� �ʿ��Ѱ� �ƴϰ�, ��ȣ�� �Ǵ��ϴ� ��Į���� �ʿ��ϴ�.
		return x * other.y - y * other.x;
	}
};

struct ObjectStat
{
	float hp = 10;
	float atk = 10;
	float def = 5;
	float attack_duration = 0;
	float attack_range = 0;
	float moveForce = 10;
	float jumpPower = 500;

};

struct RectanglePos
{
	Vector TopLeft;
	Vector TopRight;
	Vector BottomLeft;
	Vector BottomRight;
};

//////////////////


// ���а� �簢���� �浹üũ
bool LineIntersectsAABB(Vector p0, Vector p1, const RECT& rect, Vector& outNormal, Vector& outPos, float& t);