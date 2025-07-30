#include "pch.h"
#include "ResourceManager.h"
#include "DXBitmap.h"
#include "Texture.h"

void ResourceManager::Init(HWND hwnd, fs::path directory)
{
    _textures.clear();

	_hwnd = hwnd;
	_resourcePath = directory;

	CreateTextureVec(directory);

}

void ResourceManager::Destroy()
{
    for (auto& [folderName, fileMap] : _textures)
    {
        for (auto& [fileName, bitmapVec] : fileMap)
        {
            for (DXBitmap* bmp : bitmapVec)
            {
                delete bmp;
            }
            bitmapVec.clear();
        }
        fileMap.clear();
    }

    _textures.clear();
}

void ResourceManager::CreateTextureVec(fs::path directory)
{
    directory = directory.lexically_normal();

    if (!fs::exists(directory) || !fs::is_directory(directory))
        return;

    //�ֻ��� ���� ��
    for (const auto& firstentry : fs::directory_iterator(directory))
    {
        if (firstentry.is_directory())
        {
            std::string UpperName = (firstentry.path().filename().string());

            if (!fs::exists(firstentry))
                continue;

            //�ߺз�
            for (const auto& Middleentry : fs::directory_iterator(firstentry))
            {
                std::string MiddleName = (Middleentry.path().filename().string());

                if (!fs::exists(Middleentry))
                    continue;

                //�̹��� �����Ϳ� ����
                for (const auto& Lowleentry : fs::directory_iterator(Middleentry))
                {
                    std::wstring temp = Lowleentry.path().c_str();

                    DXBitmap* bitmap = new DXBitmap();
                    bitmap->Load(temp);

                    _textures[UpperName][MiddleName].push_back(bitmap);

                }
            }

        }
    }

}

//DXBitmap* ResourceManager::LoadDXBitmap(std::string key, std::wstring path)
//{
//	if (_bitmap.find(key) != _bitmap.end())
//	{
//		// �̹� �����ϴ� Ű��� ����
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
