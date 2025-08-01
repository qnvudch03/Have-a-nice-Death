#pragma once
#include "Animaotr.h"

class Texture;

class Object
{
public:
	virtual void Init() {}
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);
	virtual void Destroy();

	Object(RenderLayer rendertype, DrawAnchor drawanchor) : _RenderType(rendertype) , anchorPosition(drawanchor)
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
	Animator animaotr;
	DrawAnchor anchorPosition = DrawAnchor::Positiondefault;

private:
	//std::vector<Texture*>* _Playtextures = nullptr;
	//std::unordered_map<std::string, std::vector<Texture*>>* _OwnTextures;
	RenderLayer _RenderType = RenderLayer::Max;
	Vector _pos = {};


	float _stackIndexCounter = 0;

};

