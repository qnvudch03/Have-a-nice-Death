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

private:
	// ±âº» À©µµ¿ì ·»´õ¸µ ÆÄ¶ó¹ÌÅÍ
	HWND	_hwnd;
	RECT	_rect;
	HWND	_subhwnd;
	RECT	_subwidnowrect;

	ID2D1HwndRenderTarget* _dxRenderTarget = nullptr;
	ID2D1HwndRenderTarget* _dxSubRenderTarget = nullptr;
	ID2D1Factory* _dxFactory = nullptr;
	IWICImagingFactory* _wicFactory = nullptr;

	bool _isSubWindowOpen = false;

	// ¾À
	Scene* _currScene = nullptr;

	// Input
	std::function<void(Vector pos)> _onLeftMousecliked;
	std::function<void(Vector pos)> _onRightMousecliked;

	void MappingFunctions();
	std::map<std::string, std::function<void()>> _actionMap;

	//Debug
	DebugLenderer* _debugLenderer = nullptr;

public:
	// Major function
	void Init(HWND hwnd, HWND subhwnd);
	void Update(HWND hwnd);
	void Render();

	void PlayGame();
	void EditGame();
	void ExitGame();

	void Destroy() override;


	//  getter / setter
	ID2D1HwndRenderTarget* GetSubRenderTarget() { return _dxSubRenderTarget; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return _dxRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return _wicFactory; }

	void SetSubWinOpen(bool isOpen) { _isSubWindowOpen = isOpen; }

	DebugLenderer* GetDebugLenderer() { return _debugLenderer; }

	// ¾À
	SceneLoader* sceneLoader = nullptr;

	Scene* GetCurrentScence() { return _currScene; }
	static Scene* GetScene();
	static class GameScene* GetGameScene();

	void CheckReservedScene();
	void GoToLobby();


	// Input
	std::function<void()> BindGameActionByName(std::string actionName);

	void OnLeftClickEvent();
	void OnRightClickEvent();

	void OnMultiplyKeypadPressed();
	void OnAddKeypadPressed();
	void OnMinusKeypadPressed();


	void OnSubWinLectMouseClicked(Vector mouseClickedPos);
	void OnSubWinRightMouseClicked(Vector mouseClickedPos);
	void OnWhillMove(bool num);

	WindowMediator WinMediator;
};

