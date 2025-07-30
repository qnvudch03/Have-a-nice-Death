#include "pch.h"
#include "Object.h"
#include "Texture.h"

void Object::Render(ID2D1RenderTarget* renderTarget)
{
	for (auto iter : _OwnTextures)
	{
		iter->Render(renderTarget, GetPos());
	}
}