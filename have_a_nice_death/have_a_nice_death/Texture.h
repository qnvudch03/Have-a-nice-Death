#pragma once

class DXBitmap;

class Texture
{
public:
	Texture(ID2D1HwndRenderTarget* mainRenderTarget, DXBitmap* bitmap, int32 SizeX, int32 SizeY) : _bitmap(bitmap), _textureSizeX(SizeX), _textureSizeY(SizeY), _mainWindowRenderTarget(mainRenderTarget){}
	~Texture();

	Vector GetTextureSize() { return Vector(_textureSizeX, _textureSizeY); }

	// �ش� ���ҽ��� �׷����� �κ�
	void Render(ID2D1RenderTarget* renderTarget, Vector pos, ImageAnchor drawAnchor = ImageAnchor::Topleft, bool FlipOrder = false);
	void RenderSlope(ID2D1RenderTarget* renderTarget, Vector pos, Vector ratio, ImageAnchor drawAnchor = ImageAnchor::Topleft,bool FlipOrder = false);
	void RenderCustomSize(ID2D1RenderTarget* renderTarget, Vector pos, Vector size, ImageAnchor drawAnchor = ImageAnchor::Topleft, bool FlipOrder = false);
	void RenderWinOffset(ID2D1RenderTarget* renderTarget, Vector pos, ImageAnchor drawAnchor = ImageAnchor::Topleft, Vector WinOffset = Vector(0,0));

	void SetFileFath(std::wstring fileName) { FilePath = fileName; }
	std::wstring GetFileFath() { return FilePath; }
	void SetDrawBound(bool drawbound) { drawBound = drawbound; }

	void SetRenderedPosition(int32 x, int32 y) { _renderingOffsetX = x; _renderingOffsetY = y; }

	//void ReSizeTexture(Vector size) { _textureSizeX = size.x; _textureSizeY = size.y; }
	//void SetDrawSize(Vector size) { _textureDrawSizeX = size.x; _textureDrawSizeY = size.y; }

private:
	// �ؽ�ó�� �׸������� ����

	DXBitmap* _bitmap = nullptr;
	DXBitmap* _subbitmap = nullptr;

	//���������� �׸� �� �ܼ� �񱳿��� Ȯ�ο� (�Ź� Game���� �������� �ð� ���� ���ݾ�)
	ID2D1RenderTarget* _mainWindowRenderTarget = nullptr;

	int32 _textureSizeX = 0;	// ���� �ؽ�ó ũ��
	int32 _textureSizeY = 0;

	int32 _renderingOffsetX = 0; //�׷��� �� ����ġ
	int32 _renderingOffsetY = 0;

	Vector WindowOffset = Vector(0, 0);

	Vector _textureRatio = Vector(1, 1);

	std::wstring FilePath;

	bool drawBound = false;

};

