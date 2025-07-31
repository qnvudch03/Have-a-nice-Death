#pragma once

class DXBitmap;

class Texture
{
public:
	Texture(DXBitmap* bitmap, int32 SizeX, int32 SizeY) : _bitmap(bitmap), _textureSizeX(SizeX), _textureSizeY(SizeY) {}
	~Texture();


	void Destroy();

	// �ش� ���ҽ��� �׷����� �κ�
	void Render(ID2D1RenderTarget* renderTarget, Vector pos, DrawAnchor drawAnchor = DrawAnchor::Topleft);

	void SetRenderedPosition(int32 x, int32 y) { _renderingOffsetX = x; _renderingOffsetY = y; }

private:
	// �ؽ�ó�� �׸������� ����
	HDC		_textureHdc = 0;

	DXBitmap* _bitmap = nullptr;

	int32 _textureSizeX = 0;	// ���� �ؽ�ó ũ��
	int32 _textureSizeY = 0;

	int32 _renderingOffsetX = 0; //�׷��� �� ����ġ
	int32 _renderingOffsetY = 0;

};

