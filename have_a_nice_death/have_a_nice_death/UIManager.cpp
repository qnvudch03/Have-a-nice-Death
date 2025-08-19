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
	//���ӻ� �����ϴ� ��� UI�� ���⼭ �ʱ�ȭ �Ѵ�.
	_gameUI.clear();

	CreateUIVec(directory);

}

//void UIManager::Update(Scene* scene)
//{
//	//���� ���� �޾Ƽ�, �ű⿡ �ִ� UI�� ������Ʈ
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
//		//�켱 ������, �κ�Ŵ� ������Ʈ �� �ʿ䰡 ����
//		return;
//	}
//
//}

void UIManager::OnMouseButtonClicked(Vector pos)
{
	//TODO
	//���� Ȱ��ȭ�� �� buttonUI�� ��ȸ�ؼ�, �ڱ�� ��ġ�� ��ġ���� Ȯ���ϰ� ����

	std::vector<UI*>* CurrentSceneUI = GetSceneUI(Game::GetInstance()->GetCurrentScence());

	if (CurrentSceneUI == nullptr)
		return;

	for (auto Iter : *CurrentSceneUI)
	{
		//Ȱ��ȭ �� �͸� üũ
		if (!Iter->IsOpen())
			continue;

		//�̹��� Ÿ���� UI ����
		if (Iter->GetType() == UiType::Image)
			continue;

		UIButton* btn = static_cast<UIButton*>(Iter);

		if (btn->CheckClicked(pos))
		{
			//�켱 ���� ���� ���� ������ �� ��ư�� ����ǰ� ����
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

    //�ֻ��� ���� ��
    for (const auto& firstentry : fs::directory_iterator(directory))
    {
        if (firstentry.is_directory())
        {
            std::string UpperName = (firstentry.path().filename().string());

            if (!fs::exists(firstentry))
                continue;

			std::vector<std::pair<std::string, Texture*>> textures;

			//�̹��� �����Ϳ� ����
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

				//UI Ÿ���� ��ư�� ���
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

				//�׳� ����� �̹��� �� ���
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
