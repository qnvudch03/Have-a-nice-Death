#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "WindowMediator.h"

class DebugLenderer;

class SceneLoader;

class Game : public Singleton<Game>
{
public:
	Game();
	~Game();

	void Init(HWND hwnd, HWND subhwnd);
	//void InitSubWin();
	void Update(HWND hwnd);
	void Render();
	void OnLeftClickEvent();
	void CheckReservedScene();

	void SetSubWinOpen(bool isOpen) { isSubWindowOpen = isOpen; }

	static Scene* GetScene();
	static class GameScene* GetGameScene();

	std::function<void()> BindGameActionByName(std::string actionName);

	Scene* GetCurrentScence() { return _currScene; }

	ID2D1HwndRenderTarget* GetSubRenderTarget() { return _dxSubRenderTarget; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return _dxRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return _wicFactory; }

	SceneLoader* sceneLoader = nullptr;

	DebugLenderer* GetDebugLenderer() { return debugLenderer; }

	WindowMediator WinMediator;

public:
	void Destroy() override;

private:
	void changeGameScene();

private:

	HWND	_hwnd;
	RECT	_rect;
	HWND	_subhwnd;
	RECT	_subwidnowrect;

	ID2D1HwndRenderTarget* _dxRenderTarget = nullptr;
	ID2D1HwndRenderTarget* _dxSubRenderTarget = nullptr;


	ID2D1Factory* _dxFactory = nullptr;
	IWICImagingFactory* _wicFactory = nullptr;

	//Draw Text
	/*IDWriteFactory* m_pDWriteFactory = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;*/

	bool DegubMode = false;
	bool isSubWindowOpen = false;

	//void InitDirectWrite();

	//void DrawText(ID2D1RenderTarget* renderTarget, const wchar_t* text, float x, float y);

	void MappingFunctions();

	Scene* _currScene = nullptr;
	std::function<void(Vector pos)> _onLeftMousecliked;

	std::map<std::string, std::function<void()>> _actionMap;

	//게임상에서 UI로 작동할 모든 함수들

	void PlayGame();
	void EditGame();
	void ExitGame();

	//이거는 게임씬에있는 함수랑 연결시켜 보는게 어떨까?
	//void SelectCurse();

	DebugLenderer* debugLenderer = nullptr;


public:
	//에디터 씬 데이터
	void OnSubWinLectMouseClicked(Vector mouseClickedPos);
	void OnSubWinRightMouseClicked(Vector mouseClickedPos);
	void OnSubWinNumber2Pressed();
	void OnSubWinNumber8Pressed();

	void OnMouseWhillMoved(bool num);
};

