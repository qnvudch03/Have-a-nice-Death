#pragma once
#include "Singleton.h"
#include "Scene.h"

class Game : public Singleton<Game>
{
public:
	Game();
	~Game();

	void Init(HWND hwnd);
	void Update();
	void Render();
	void OnLeftClickEvent();

	static Scene* GetScene();
	static class GameScene* GetGameScene();

	Scene* GetCurrentScence() { return _currScene; }

	ID2D1HwndRenderTarget* GetRenderTarget() { return _dxRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return _wicFactory; }

protected:
	void Destroy() override;

private:
	void changeGameScene();

private:

	HWND	_hwnd;
	RECT	_rect;

	ID2D1Factory* _dxFactory = nullptr;
	ID2D1HwndRenderTarget* _dxRenderTarget = nullptr;
	IWICImagingFactory* _wicFactory = nullptr;

	//Draw Text
	IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;

	void InitDirectWrite();

	void DrawText(ID2D1RenderTarget* renderTarget, const wchar_t* text, float x, float y);

	//// 해제 함수
	//void CleanupDirectWrite();

	Scene* _currScene = nullptr;
	std::function<void(Vector pos)> _onLeftMousecliked;
};

