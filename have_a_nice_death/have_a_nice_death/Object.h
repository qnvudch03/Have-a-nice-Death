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
	virtual void RenderWithWinOffset(ID2D1RenderTarget* renderTarget, Vector WinOffset);
	virtual void RenderWithOpacity(ID2D1RenderTarget* renderTarget, float opacity);
	virtual void SetDebugMode(bool debugMode);
	virtual void Destroy();
	virtual void SetCollider();

	Object(RenderLayer rendertype, ImageAnchor drawanchor) : _RenderType(rendertype) , anchorPosition(drawanchor)
	{

	}

	virtual ~Object()
	{
		if (collider != nullptr)
		{
			delete collider;
			collider = nullptr;
		}
	}


	RenderLayer GetRenderLayer() { return _RenderType; }
	void SetAnimaotrTextures(std::vector<Texture*>* texturesvec, bool IsLoop = true, bool IsAttackAnim = false, int32 HitBoxIndex = -1)
	{ 
		animator.SetAnimTexture(texturesvec, IsLoop, IsAttackAnim, HitBoxIndex);
		animator.TextureNum = (*texturesvec).size();
	}

	void SetManyAnimaotrTextures(std::vector<Texture*>* texturesvec, bool IsLoop = true, bool IsAttackAnim = false, std::vector<int32> HitBoxIndexs = {})
	{
		animator.SetMultiAnimTexture(texturesvec, IsLoop, IsAttackAnim, HitBoxIndexs);
		animator.TextureNum = (*texturesvec).size();
	}

	Vector GetPos() { return _pos; }
	void SetPos(Vector pos) { _pos = pos; }

	//애니메이션 관련
	Animator animator;
	ImageAnchor anchorPosition = ImageAnchor::Positiondefault;
	bool renderingFlipOrder = false;
	bool custumRenderSizeOrder = false;
	Vector custumRenderSize = Vector(0, 0);

	//콜라이더
	Collider* collider = nullptr;

private:

	RenderLayer _RenderType = RenderLayer::Max;
	Vector _pos = {};
};

