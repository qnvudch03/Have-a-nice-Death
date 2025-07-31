#pragma once

#include "Singleton.h"

class DXBitmap;
class Texture;

// ���ҽ� ������ ���ӿ��� �پ��ϰ� ����.
// �ؽ�ó / �޽� / ���� / ����Ʈ ���..
// ��� ���ҽ����� �����ϴ� �Ŵ���
class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	HWND _hwnd;
	fs::path _resourcePath;

	void Init(HWND hwnd, fs::path directory);
	void Destroy();	// ���ҽ� ����

	void CreateTextureVec(fs::path directory);

	void LoadTexture(std::string name, std::wstring path, int32 countX = 1, int32 countY = 1);
	std::vector<Texture*>* GetTextures(std::string UpperName, std::string MiddleName);

	const SpriteInfo* GetSpriteInfo(std::string key);

	//DXBitmap* LoadDXBitmap(std::string key, std::wstring path);

private:
	//std::unordered_map<std::string, Texture*> _textures;
	std::unordered_map<std::string, SpriteInfo>	_spriteNames;

	std::map<std::string, std::unordered_map<std::string, std::vector<Texture*>>> _textures;
};

