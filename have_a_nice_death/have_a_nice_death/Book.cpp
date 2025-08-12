#include "pch.h"
#include "Book.h"
#include "Texture.h"

#include "LivingObject.h"

void Book::Update()
{
	pos.x = owner->GetPos().x + owner->forwordDirection * offset.x;
	pos.y = owner->GetPos().y + offset.y;
}

void Book::SetBookState(std::string state)
{
	if (!state.compare("Idle"))
	{
		animator.SetAnimTexture(&(*ownTextures)[state], true);
	}

	else if (!state.compare("IdleUturn"))
	{
		animator.SetAnimTexture(&(*ownTextures)[state], false);
	}
	
}
