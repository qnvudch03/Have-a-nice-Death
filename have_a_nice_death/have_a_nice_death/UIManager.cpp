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

void UIManager::Update(Scene* scene)
{
	//현재 씬을 받아서, 거기에 있는 UI만 업데이트
	std::string CurrentScene;

	if (dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
	{
		CurrentScene = "GameScene";
	}

	else if (dynamic_cast<Lobby*>(Game::GetInstance()->GetCurrentScence()) != nullptr)
	{
		CurrentScene = "RobbyScene";

		//우선 지금은, 로비씽는 업데이트 할 필요가 없음
		return;
	}

	for (auto& Iter : _gameUI[CurrentScene])
	{
		Iter->Update();
	}

}

void UIManager::OnMouseButtonClicked(Vector pos)
{
	//TODO
	//현재 활성화가 된 buttonUI를 순회해서, 자기와 위치가 겹치는지 확인하고 실행
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
					_gameUI[UpperName].push_back(new UIButton(name, texture.second, uiPosition));
				}

				//그냥 평범한 이미지 일 경우
				else
				{
					_gameUI[UpperName].push_back(new UIImage(name, texture.second, uiPosition));
				}
			}

			uidata.clear();

        }
    }
}

void UIManager::Destroy()
{
	//TODO
	//저 Map 없애기
}
