#include "pch.h"
#include "UIManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "Game.h"
#include "DXBitmap.h"
#include "UI.h"
#include "UIButton.h"
#include "UIImage.h"

void UIManager::Init(fs::path directory)
{
	//게임상에 존재하는 모든 UI를 여기서 초기화 한다.
	_gameUI.clear();

	CreateUIVec(directory);

}

//void UIManager::Update(Scene* scene)
//{
//	//현재 씬을 받아서, 거기에 있는 UI만 업데이트
//	std::string CurrentScene;
//
//	if (dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
//	{
//		CurrentScene = "GameScene";
//	}
//
//	else if (dynamic_cast<Lobby*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
//	{
//		CurrentScene = "RobbyScene";
//
//		//우선 지금은, 로비씽는 업데이트 할 필요가 없음
//		return;
//	}
//
//}

void UIManager::OnMouseButtonClicked(Vector pos)
{
	//TODO
	//현재 활성화가 된 buttonUI를 순회해서, 자기와 위치가 겹치는지 확인하고 실행

	std::vector<UI*>* CurrentSceneUI = GetSceneUI(Game::GetInstance()->GetCurrentScence());

	if (CurrentSceneUI == nullptr)
		return;

	for (auto Iter : *CurrentSceneUI)
	{
		//활성화 된 것만 체크
		if (!Iter->IsOpen())
			continue;

		//이미지 타입의 UI 필터
		if (Iter->GetType() == UiType::Image)
			continue;

		UIButton* btn = static_cast<UIButton*>(Iter);

		if (btn->CheckClicked(pos))
		{
			//우선 제일 먼저 눌림 판정이 난 버튼만 실행되게 하자
			btn->DoAction();

			return;
		}

	}
}

std::vector<UI*>* UIManager::GetSceneUI(Scene* scene)
{
	std::string CurrentScene;

	if (dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
	{
		CurrentScene = "GameScene";
	}

	else if (dynamic_cast<Lobby*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
	{
		CurrentScene = "RobbyScene";
	}


	if (_gameUI.find(CurrentScene) == _gameUI.end())
	{
		return nullptr;
	}
	
	return (&_gameUI[CurrentScene]);
}

void UIManager::CreateUIVec(fs::path directory)
{
    directory = directory.lexically_normal();

    if (!fs::exists(directory) || !fs::is_directory(directory))
        return;

	std::map<std::string, Vector> uidata;

    //최상위 폴더 명
    for (const auto& firstentry : fs::directory_iterator(directory))
    {
        if (firstentry.is_directory())
        {
            std::string UpperName = (firstentry.path().filename().string());

            if (!fs::exists(firstentry))
                continue;

			std::vector<std::pair<std::string, Texture*>> textures;

			//이미지 포인터에 매핑
			for (const auto& Lowleentry : fs::directory_iterator(firstentry))
			{
				//std::vector<Vector> offsetVector;
				std::wstring FileName = Lowleentry.path().c_str();
				

                if (FileName[FileName.size() - 4] == L'.' &&
                    FileName[FileName.size() - 3] == L't' &&
                    FileName[FileName.size() - 2] == L'x' &&
                    FileName[FileName.size() - 1] == L't')
                {
                    std::ifstream  file(FileName);
                    std::string line;

					while (std::getline(file, line)) {
						std::istringstream iss(line);

						std::string name;
						int x, y = 0;

						if (iss >> name >> x >> y) {
							uidata[name] = Vector( x, y);
						}
					}

                    continue;
                }

				DXBitmap* bitmap = new DXBitmap();
				bitmap->Load(FileName);

				Texture* UITexture = new Texture(bitmap, bitmap->GetBitmapSize().Width, bitmap->GetBitmapSize().Height);

				textures.emplace_back(Lowleentry.path().filename().string(), UITexture);

			}

			for (auto& texture : textures)
			{
				std::string name = texture.first.substr(0, texture.first.size() - 4);
				Vector uiPosition = uidata[name];

				//UI 타입이 버튼일 경우
				if (name.find("BTN") != std::string::npos)
				{
					UIButton* btn = new UIButton(name, texture.second, uiPosition);
					_gameUI[UpperName].push_back(btn);
					_buttons.push_back(btn);
				}

				else if (name.find("BackGround") != std::string::npos)
				{
					UIImage* img = new UIImage(name, texture.second, uiPosition);
					img->SetRatioX(20);
					img->SetRatioY(8);
					_gameUI[UpperName].push_back(img);
					_images.push_back(img);
				}

				//그냥 평범한 이미지 일 경우
				else
				{
					UIImage* img = new UIImage(name, texture.second, uiPosition);
					_gameUI[UpperName].push_back(img);
					_images.push_back(img);
				}
			}

			uidata.clear();

        }
    }
}

void UIManager::Destroy()
{
	//TODO
	for (auto& [UIFolerName, UIVec] : _gameUI)
	{
		for (auto Iter : UIVec)
		{
			delete Iter;
			Iter = nullptr;
		}
		UIVec.clear();
	}

	_buttons.clear();
	_images.clear();
}
