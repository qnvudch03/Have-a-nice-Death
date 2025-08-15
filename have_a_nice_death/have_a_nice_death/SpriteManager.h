#pragma once

#include "Singleton.h"

class DXBitmap;
class Texture;

// 리소스 개념이 게임에서 다양하게 등장.
// 텍스처 / 메시 / 사운드 / 이펙트 등등..
// 모든 리소스들을 관리하는 매니저
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

	void LoadTexture(std::string name, std::wstring path, int32 countX = 1, int32 countY = 1);
	std::vector<Texture*>* GetTextures(std::string UpperName, std::string MiddleName);
	std::map<std::string, std::vector<Texture*>>* GetTextureMap(std::string UpperName);

	const SpriteInfo* GetSpriteInfo(std::string key);

	//DXBitmap* LoadDXBitmap(std::string key, std::wstring path);

private:
	//std::unordered_map<std::string, Texture*> _textures;
	std::map<std::string, SpriteInfo>	_spriteNames;

	std::map<std::string, std::map<std::string, std::vector<Texture*>>> _textures;
};

