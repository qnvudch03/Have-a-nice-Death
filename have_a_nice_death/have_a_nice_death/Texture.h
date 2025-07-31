#pragma once

class DXBitmap;

class Texture
{
public:
	Texture(DXBitmap* bitmap, int32 SizeX, int32 SizeY) : _bitmap(bitmap), _textureSizeX(SizeX), _textureSizeY(SizeY) {}
	~Texture();


	void Destroy();

	// 해당 리소스가 그려지는 부분
	void Render(ID2D1RenderTarget* renderTarget, Vector pos, DrawAnchor drawAnchor = DrawAnchor::Topleft);

	void SetRenderedPosition(int32 x, int32 y) { _renderingOffsetX = x; _renderingOffsetY = y; }

private:
	// 텍스처를 그리기위한 변수
	HDC		_textureHdc = 0;

	DXBitmap* _bitmap = nullptr;

	int32 _textureSizeX = 0;	// 원본 텍스처 크기
	int32 _textureSizeY = 0;

	int32 _renderingOffsetX = 0; //그려질 때 가중치
	int32 _renderingOffsetY = 0;

};

