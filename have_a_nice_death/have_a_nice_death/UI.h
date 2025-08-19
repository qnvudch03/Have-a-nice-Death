#pragma once
#include "Texture.h"

class UI
{
public:
	UI(std::string name, Texture* texture, Vector pos) : _name(name), _uiTexture(texture), _targetPos(pos){}
	virtual ~UI() = default;

public:
	virtual void Init() {}
	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* renderTarget);
	virtual void Open() { _isOpen = true; }
	virtual void Close() { _isOpen = false; }

	UiType GetType() { return _UiType; }

	bool IsOpen() const { return _isOpen; }
	void SetOpen(bool open) { _isOpen = open; }

	void SetCurrentpos(Vector pos) { _currentPos = pos; }
	void SetTargetpos(Vector pos) { _targetPos = pos; }
	void SetMoveDirection(Vector dir, float speed = 1500) { movingDirect = dir; movingSpeed = speed, _isMoveable = true; }

	void SetRatioX(float Ratio) { ratio.x = Ratio; }
	void SetRatioY(float Ratio) { ratio.y = Ratio; }

	std::string _name;
	Vector movingDirect;
	float movingSpeed = 0;

protected:
	bool _isOpen = false;

	bool _isMoveable = false;
	Vector ratio = Vector(1,1);
	Vector _currentPos = {};
	Vector _targetPos = {};
	Texture* _uiTexture = nullptr;

	UiType _UiType = UiType::UiDefault;
};

