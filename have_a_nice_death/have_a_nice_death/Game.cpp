#include "pch.h"
#include "Game.h"
#include "Scene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "UIManager.h"
#include "UI.h"
#include "DebugLenderer.h"

#include "LobbyScene.h"
#include "GameScene.h"
#include "EditorScene.h"
#include "SceneLoader.h"


Game::Game()
{
	//�κ� ��;
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

	// �̹��� �ε� �ʱ�ȭ
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));


	//��� �� �ʱ�ȭ
	MappingFunctions();

	// ���ҽ� �Ŵ��� �ʱ�ȭ
	wchar_t buffer[MAX_PATH];
	DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
	fs::path ResourcePath = fs::path(buffer) / L"../../Resources/";
	SpriteManager::GetInstance()->Init(hwnd, ResourcePath);

	//UI
	fs::path UIPath = fs::path(buffer) / L"../../UI/";
	UIManager::GetInstance()->Init(UIPath);

	// Ÿ�̸� �ʱ�ȭ
	TimeManager::GetInstance()->Init();
	// �Է� �Ŵ��� �ʱ�ȭ
	InputManager::GetInstance()->Init(hwnd);

	//���δ� �ʱ�ȭ
	sceneLoader = new SceneLoader();

	//����� ������ �ʱ�ȭ
	debugLenderer = new DebugLenderer(_dxRenderTarget);

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

void Game::CheckReservedScene()
{
	if (_currScene == nullptr)
		return;

	if (!sceneLoader->IsReserved())
		return;

	_currScene->EraseScene();
	delete _currScene;

	_currScene = sceneLoader->GetReservedScene();
	_currScene->Init();

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

	delete sceneLoader;

	delete debugLenderer;
}

void Game::MappingFunctions()
{

	_actionMap.clear();

	//��ư �Է¿� ���� �Լ� ������ �̸� �� ����
	//�̰� �������� �Ź� �ؾ� �ϳ�?? �ٸ� ����� ������?
	_actionMap = {
		{"BTN_Play",  [this]() { PlayGame(); }},
		{"BTN_Edit",  [this]() { EditGame(); }},
		{"BTN_Exit",  [this]() { ExitGame(); }}
	};
}

std::function<void()> Game::BindGameActionByName(std::string actionName)
{
	if (_actionMap.find(actionName) == _actionMap.end())
		return nullptr;

	return _actionMap[actionName];
}

void Game::PlayGame()
{
	//���� ������ ��ȯ

	if (_currScene == nullptr)
	{
		//Somthing Bad
		int apple = 0;
	}

	sceneLoader->ReserveScene(new GameScene());
}

void Game::EditGame()
{
	//������ ������ ��ȯ

	if (_currScene == nullptr)
	{
		//Somthing Bad
		int apple = 0;
	}

	_currScene->EraseScene();
	delete _currScene;

	_currScene = new EditorScene();
	_currScene->Init();

}

void Game::ExitGame()
{
}

//void Game::SelectCurse()
//{
//}

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
