#pragma once
#include "Animaotr.h"

class Texture;
class Collider;

class Object
{
public:
	virtual void Init() {}
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);
	virtual void SetDebugMode(bool debugMode);
	virtual void Destroy();
	virtual void SetCollider();

	Object(RenderLayer rendertype, ImageAnchor drawanchor) : _RenderType(rendertype) , anchorPosition(drawanchor)
	{

	}

	virtual ~Object()
	{
		
	}


	RenderLayer GetRenderLayer() { return _RenderType; }
	void SetAnimaotrTextures(std::vector<Texture*>* texturesvec, bool IsLoop = true)
	{ 
		animator.SetAnimTexture(texturesvec, IsLoop);
		animator.TextureNum = (*texturesvec).size();
	}

	Vector GetPos() { return _pos; }
	void SetPos(Vector pos) { _pos = pos; }

	//애니메이션 관련
	Animator animator;
	std::map<std::string, float> stateAnimSpeedMap;
	ImageAnchor anchorPosition = ImageAnchor::Positiondefault;
	bool renderingFlipOrder = false;

	//콜라이더
	Collider* collider = nullptr;

private:

	RenderLayer _RenderType = RenderLayer::Max;
	Vector _pos = {};

	ID2D1RenderTarget* _renderTarget = nullptr;
};

