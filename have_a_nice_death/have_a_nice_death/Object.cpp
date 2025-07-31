#include "pch.h"
#include "Object.h"
#include "Texture.h"

void Object::Render(ID2D1RenderTarget* renderTarget)
{
	/*for (auto& iter : *_Playtextures)
	{
		iter->Render(renderTarget, GetPos());
	}*/

	animaotr.GetAnimTexture()->Render(renderTarget, GetPos(), isdrawCenter);

}

void Object::Update(float deltaTime)
{
	animaotr.Update(deltaTime);

}