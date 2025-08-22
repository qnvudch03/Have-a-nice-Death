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

void Game::Init(HWND hwnd, HWND subhwnd)
{
	srand((uint32)time(0));
	_hwnd = hwnd;
	_subhwnd = subhwnd;

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dxFactory);

	//Create MainWindow RenderTarget
	{
		::GetClientRect(hwnd, &_rect);

		// dx init
		D2D1_SIZE_U size = D2D1::SizeU(_rect.right - _rect.left, _rect.bottom - _rect.top);

		// Create a Direct2D render target.
		_dxFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&_dxRenderTarget);

		//// �̹��� �ε� �ʱ�ȭ
		//CoInitialize(NULL);
		//CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
	}
	
	//Create SubWindow RenderTarget
	{
		::GetClientRect(subhwnd, &_subwidnowrect);

		// dx init
		//D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dxFactory);

		D2D1_SIZE_U size = D2D1::SizeU(_subwidnowrect.right - _subwidnowrect.left, _subwidnowrect.bottom - _subwidnowrect.top);

		// Create a Direct2D render target.
		_dxFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(subhwnd, size),
			&_dxSubRenderTarget);

		// �̹��� �ε� �ʱ�ȭ
		CoInitialize(NULL);
		CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
	}


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

	_onLeftMousecliked = [this](Vector pos)
		{
			UIManager::GetInstance()->OnMouseButtonClicked(pos);
			_currScene->OnLeftButtonClicked(pos);
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

	//�� ����� �ϴ��� subWindow�� ��
	isSubWindowOpen = false;
	WinMediator.SetActivate(false);

	if (auto gamdScene = dynamic_cast<GameScene*>(_currScene))
	{
		gamdScene->Init();
	}

	else if (auto editorScene = dynamic_cast<EditorScene*>(_currScene))
	{
		isSubWindowOpen = true;
		editorScene->SetSubWindow(_dxSubRenderTarget, _subhwnd);
		editorScene->Init();

		WinMediator.ReFresh();
	}
	

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

	sceneLoader->ReserveScene(new EditorScene());
}

void Game::ExitGame()
{
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


	if (isSubWindowOpen)
	{
		GetScene()->RenderSubWin();
	}

}

//�̺�Ʈ�� �Լ���

void Game::OnSubWinLectMouseClicked(Vector mouseClickedPos)
{
	WinMediator.OnSubWinClicked(-1, mouseClickedPos);
}

void Game::OnSubWinRightMouseClicked(Vector mouseClickedPos)
{
	WinMediator.OnSubWinClicked(1, mouseClickedPos);
}

void Game::OnSubWinNumber2Pressed()
{
	WinMediator.OnSubWinNumPressed(2);
}

void Game::OnSubWinNumber8Pressed()
{
	WinMediator.OnSubWinNumPressed(8);
}

void Game::OnMouseWhillMoved(bool num)
{
	WinMediator.OnMouseWhillMove(num);
}
