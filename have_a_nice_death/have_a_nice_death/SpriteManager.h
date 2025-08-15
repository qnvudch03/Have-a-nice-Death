#pragma once

#include "Singleton.h"

class DXBitmap;
class Texture;

// ���ҽ� ������ ���ӿ��� �پ��ϰ� ����.
// �ؽ�ó / �޽� / ���� / ����Ʈ ���..
// ��� ���ҽ����� �����ϴ� �Ŵ���
class SpriteManager : public Singleton<SpriteManager>
{
	friend Singleton<SpriteManager>;
	SpriteManager() {}
public:

	HWND _hwnd;
	fs::path _spritePath;

	void Init(HWND hwnd, fs::path directory);
	void Destroy();	// ���ҽ� ����

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

