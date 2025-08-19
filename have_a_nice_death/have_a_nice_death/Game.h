#pragma once
#include "Singleton.h"
#include "Scene.h"

class DebugLenderer;

class SceneLoader;

class Game : public Singleton<Game>
{
public:
	Game();
	~Game();

	void Init(HWND hwnd);
	void Update();
	void Render();
	void OnLeftClickEvent();
	void CheckReservedScene();

	static Scene* GetScene();
	static class GameScene* GetGameScene();

	std::function<void()> BindGameActionByName(std::string actionName);

	Scene* GetCurrentScence() { return _currScene; }

	ID2D1HwndRenderTarget* GetRenderTarget() { return _dxRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return _wicFactory; }

	SceneLoader* sceneLoader = nullptr;

	DebugLenderer* GetDebugLenderer() { return debugLenderer; }

public:
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

	bool DegubMode = false;

	void InitDirectWrite();

	void DrawText(ID2D1RenderTarget* renderTarget, const wchar_t* text, float x, float y);

	void MappingFunctions();

	Scene* _currScene = nullptr;
	std::function<void(Vector pos)> _onLeftMousecliked;

	std::map<std::string, std::function<void()>> _actionMap;

	//���ӻ󿡼� UI�� �۵��� ��� �Լ���

	void PlayGame();
	void EditGame();
	void ExitGame();

	//�̰Ŵ� ���Ӿ����ִ� �Լ��� ������� ���°� ���?
	//void SelectCurse();

	DebugLenderer* debugLenderer = nullptr;
};

