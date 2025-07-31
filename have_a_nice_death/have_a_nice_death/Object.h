#pragma once
#include "Animaotr.h"

class Texture;

class Object
{
public:
	virtual void Init() {}
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);

	Object(RenderLayer rendertype, bool haveToDrawCenter) : _RenderType(rendertype) , isdrawCenter(haveToDrawCenter)
	{

	}

	virtual ~Object() = default;

	RenderLayer GetRenderLayer() { return _RenderType; }
	void SetPlayTexture(std::vector<Texture*>* texturesvec)
	{ 
		animaotr.SetAnimTexture(texturesvec);
		animaotr.TextureNum = (*texturesvec).size();
	}

	Vector GetPos() { return _pos; }
	void SetPos(Vector pos) { _pos = pos; }

	//애니메이션 관련
	Animaotr animaotr;
	bool isdrawCenter = false;

	//void Destory();

private:
	//std::vector<Texture*>* _Playtextures = nullptr;
	//std::unordered_map<std::string, std::vector<Texture*>>* _OwnTextures;
	RenderLayer _RenderType = RenderLayer::Max;
	Vector _pos = {};


	float _stackIndexCounter = 0;

};

