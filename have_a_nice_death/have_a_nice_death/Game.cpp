#include "pch.h"
#include "Game.h"
#include "Scene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include "LobbyScene.h"
#include "GameScene.h"


Game::Game()
{
	//로비 씬;
	_currScene = new Lobby();
	//_currScene = new GameScene();
}

Game::~Game()
{
	//TODO memory LEEK
	//ResourceManager::GetInstance()->Destroy();
}

void Game::Init(HWND hwnd)
{
	srand((uint32)time(0));
	_hwnd = hwnd;

	::GetClientRect(hwnd, &_rect);

	// dx init
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dxFactory);

	D2D1_SIZE_U size = D2D1::SizeU(_rect.right - _rect.left, _rect.bottom - _rect.top);

	// Create a Direct2D render target.
	_dxFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size),
		&_dxRenderTarget);

	// 이미지 로드 초기화
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));


	// 리소스 매니저 초기화
	wchar_t buffer[MAX_PATH];
	DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
	fs::path currentPath = fs::path(buffer) / L"../../Resources/";
	ResourceManager::GetInstance()->Init(hwnd, currentPath);


	// 타이머 초기화
	TimeManager::GetInstance()->Init();
	// 입력 매니저 초기화
	InputManager::GetInstance()->Init(hwnd);


	_currScene->Init();

}

void Game::OnLeftClickEvent()
{
	Vector mousePos = InputManager::GetInstance()->GetMousePos();

	//Todo
	//마우스 위치가 게임 시작인지, 에디터인지, 게임종료인지
}

Scene* Game::GetScene()
{
	if (GetInstance() != nullptr)
	{
		return GetInstance()->_currScene;
	}

	return nullptr;
}

GameScene* Game::GetGameScene()
{
	if (GetInstance())
	{
		return dynamic_cast<GameScene*>(GetInstance()->_currScene);
	}
	return nullptr;
}

void Game::Destroy()
{
	int A = 10;
}

void Game::Update()
{
	TimeManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	GetScene()->Update(TimeManager::GetDeltaTime());

}

void Game::Render()
{
	_dxRenderTarget->BeginDraw();
	_dxRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));


	GetScene()->Render(_dxRenderTarget);

	_dxRenderTarget->EndDraw();

}
