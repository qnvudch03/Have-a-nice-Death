#pragma once
#include "Texture.h"

class UI
{
public:
	UI(Texture* texture, Vector pos) : _uiTexture(texture), _pos(pos){}
	virtual ~UI() = default;

public:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Render(ID2D1RenderTarget* renderTarget);
	virtual void Open() { _isOpen = true; }
	virtual void Close() { _isOpen = false; }

	bool IsOpen() const { return _isOpen; }
	void SetOpen(bool open) { _isOpen = open; }

protected:
	bool _isOpen = true;
	Vector _pos = {};
	Texture* _uiTexture = nullptr;
};

