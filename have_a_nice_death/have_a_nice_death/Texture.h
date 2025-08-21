#pragma once

class DXBitmap;

class Texture
{
public:
	Texture(ID2D1HwndRenderTarget* mainRenderTarget, DXBitmap* bitmap, int32 SizeX, int32 SizeY) : _bitmap(bitmap), _textureSizeX(SizeX), _textureSizeY(SizeY), _mainWindowRenderTarget(mainRenderTarget){}
	~Texture();

	Vector GetTextureSize() { return Vector(_textureSizeX, _textureSizeY); }

	// 해당 리소스가 그려지는 부분
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
	// 텍스처를 그리기위한 변수

	DXBitmap* _bitmap = nullptr;
	DXBitmap* _subbitmap = nullptr;

	//서부윈도우 그릴 때 단순 비교연산 확인용 (매번 Game에서 가져오면 시간 많이 들잖아)
	ID2D1RenderTarget* _mainWindowRenderTarget = nullptr;

	int32 _textureSizeX = 0;	// 원본 텍스처 크기
	int32 _textureSizeY = 0;

	int32 _renderingOffsetX = 0; //그려질 때 가중치
	int32 _renderingOffsetY = 0;

	Vector WindowOffset = Vector(0, 0);

	Vector _textureRatio = Vector(1, 1);

	std::wstring FilePath;

	bool drawBound = false;

};

