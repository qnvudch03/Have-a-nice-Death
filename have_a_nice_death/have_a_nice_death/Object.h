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

	Object(RenderLayer rendertype, ImageAnchor drawanchor) : _RenderType(rendertype) , anchorPosition(drawanchor)
	{

	}

	virtual ~Object() = default;


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
	ImageAnchor anchorPosition = ImageAnchor::Positiondefault;

	bool renderingFlipOrder = false;

private:

	RenderLayer _RenderType = RenderLayer::Max;
	Vector _pos = {};
};

