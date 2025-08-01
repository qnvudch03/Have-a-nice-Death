#include "pch.h"
#include "Game.h"
#include "Scene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "UIManager.h"

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
	//CleanupDirectWrite();
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
	fs::path ResourcePath = fs::path(buffer) / L"../../Resources/";
	SpriteManager::GetInstance()->Init(hwnd, ResourcePath);

	//UI
	fs::path UIPath = fs::path(buffer) / L"../../UI/";
	UIManager::GetInstance()->Init(UIPath);


	// 타이머 초기화
	TimeManager::GetInstance()->Init();
	// 입력 매니저 초기화
	InputManager::GetInstance()->Init(hwnd);


	_currScene->Init();

	_onLeftMousecliked = [](Vector pos)
		{
			UIManager::GetInstance()->OnMouseButtonClicked(pos);
		};

}

void Game::OnLeftClickEvent()
{
	Vector mousePos = InputManager::GetInstance()->GetMousePos();

	_onLeftMousecliked(mousePos);
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
	SpriteManager::GetInstance()->Destroy();
	UIManager::GetInstance()->Destroy();
}

//void Game::InitDirectWrite()
//{
//	DWriteCreateFactory(
//		DWRITE_FACTORY_TYPE_SHARED,
//		__uuidof(IDWriteFactory),
//		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
//
//	if (m_pDWriteFactory)
//	{
//		m_pDWriteFactory->CreateTextFormat(
//			L"Segoe UI",
//			nullptr,
//			DWRITE_FONT_WEIGHT_NORMAL,
//			DWRITE_FONT_STYLE_NORMAL,
//			DWRITE_FONT_STRETCH_NORMAL,
//			32.0f,
//			L"en-us",
//			&m_pTextFormat);
//	}
//}

//void Game::DrawText(ID2D1RenderTarget* renderTarget, const wchar_t* text, float x, float y)
//{
//	if (!renderTarget || !m_pTextFormat)
//		return;
//
//	ID2D1SolidColorBrush* pBlackBrush = nullptr;
//	renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
//
//	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 500.f, y + 100.f);
//
//	renderTarget->DrawTextW(text, wcslen(text), m_pTextFormat, layoutRect, pBlackBrush);
//
//	if (pBlackBrush) pBlackBrush->Release();
//}

//void Game::CleanupDirectWrite()
//{
//	if (m_pTextFormat)
//	{
//		m_pTextFormat->Release();
//		m_pTextFormat = nullptr;
//	}
//	if (m_pDWriteFactory)
//	{
//		m_pDWriteFactory->Release();
//		m_pDWriteFactory = nullptr;
//	}
//}

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
