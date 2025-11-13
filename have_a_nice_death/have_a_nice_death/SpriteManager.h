#pragma once

#include "Singleton.h"

class DXBitmap;
class Texture;

class SpriteManager : public Singleton<SpriteManager>
{
	friend Singleton<SpriteManager>;
	SpriteManager() {}
public:

	HWND _hwnd;
	fs::path _spritePath;

	void Init(HWND hwnd, fs::path directory);
	void Destroy();	// 리소스 정리

	void CreateTextureVec(fs::path directory);

	std::vector<Texture*>* GetTextures(std::string UpperName, std::string MiddleName);
	std::map<std::string, std::vector<Texture*>>* GetTextureMap(std::string UpperName);

private:
	std::map<std::string, std::map<std::string, std::vector<Texture*>>> _textures;
};

