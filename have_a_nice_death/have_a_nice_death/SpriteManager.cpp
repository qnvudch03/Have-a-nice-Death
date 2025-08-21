#include "pch.h"
#include "SpriteManager.h"
#include "DXBitmap.h"
#include "Texture.h"
#include "Game.h"

void SpriteManager::Init(HWND hwnd, fs::path directory)
{
    _textures.clear();

	_hwnd = hwnd;
	_spritePath = directory;

	CreateTextureVec(directory);

}

void SpriteManager::Destroy()
{
    for (auto& [folderName, fileMap] : _textures)
    {
        for (auto& [fileName, bitmapVec] : fileMap)
        {
            for (Texture* bmp : bitmapVec)
            {
                delete bmp;
            }
            bitmapVec.clear();
        }
        fileMap.clear();
    }

    _textures.clear();
}

void SpriteManager::CreateTextureVec(fs::path directory)
{
    ID2D1HwndRenderTarget* mainRenderTarget = Game::GetInstance()->GetRenderTarget();

    directory = directory.lexically_normal();

    if (!fs::exists(directory) || !fs::is_directory(directory))
        return;

    //최상위 폴더 명
    for (const auto& firstentry : fs::directory_iterator(directory))
    {
        if (firstentry.is_directory())
        {
            std::string UpperName = (firstentry.path().filename().string());

            if (!fs::exists(firstentry))
                continue;

            //중분류
            for (const auto& Middleentry : fs::directory_iterator(firstentry))
            {
                std::string MiddleName = (Middleentry.path().filename().string());

                if (!fs::exists(Middleentry))
                    continue;

                //이미지 포인터에 매핑
                for (const auto& Lowleentry : fs::directory_iterator(Middleentry))
                {
                    //std::vector<Vector> offsetVector;
                    std::wstring FileName = Lowleentry.path().c_str();

                    //offset txt 파일 걸려내기
                    if (FileName[FileName.size() - 4] == L'.' &&
                        FileName[FileName.size() - 3] == L't'&&
                        FileName[FileName.size() - 2] == L'x'&&
                        FileName[FileName.size() - 1] == L't')
                    {
                        std::wifstream file(FileName);
                        if (!file.is_open())
                        {
                            continue;
                        }

                        int x, y;
                        auto& Iter = _textures[UpperName][MiddleName];
                        int pngCounter = 0;
                        while (file >> x >> y)
                        {
                            if (Iter.size() <= pngCounter)
                                break;

                            Iter[pngCounter]->SetRenderedPosition(x, y);
                            pngCounter++;
                        }

                        continue;
                    }

                    DXBitmap* bitmap = new DXBitmap();
                    bitmap->Load(FileName);

                    Texture* texture = new Texture(mainRenderTarget, bitmap, bitmap->GetBitmapSize().Width, bitmap->GetBitmapSize().Height);
                    texture->SetFileFath(FileName);

                    _textures[UpperName][MiddleName].push_back(texture);

                }
            }

        }
    }

}

std::vector<Texture*>* SpriteManager::GetTextures(std::string UpperName, std::string MiddleName)
{
    if (!_textures.contains(UpperName))
        return nullptr;

    const auto& middleMap = _textures.at(UpperName);


    if (!middleMap.contains(MiddleName))
        return nullptr;

    const auto& textures = middleMap.at(MiddleName);

    if (textures.empty())
        return nullptr;

    return const_cast<std::vector<Texture*>*>(&textures);

}

std::map<std::string, std::vector<Texture*>>* SpriteManager::GetTextureMap(std::string UpperName)
{
    if (!_textures.contains(UpperName))
        return nullptr;

    return &_textures[UpperName];
}

//DXBitmap* ResourceManager::LoadDXBitmap(std::string key, std::wstring path)
//{
//	if (_bitmap.find(key) != _bitmap.end())
//	{
//		// 이미 존재하는 키라면 리턴
//		return _bitmap[key];
//	}
//
//	fs::path fullPath = _resourcePath / path;
//
//	DXBitmap* bitmap = new DXBitmap();
//	bitmap->Load(fullPath.c_str(), countX, countY);
//	_bitmap[key] = bitmap;
//	return bitmap;
//}
