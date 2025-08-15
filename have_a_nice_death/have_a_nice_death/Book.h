#pragma once

#include "SpriteManager.h"
#include "Animaotr.h"

class LivingObject;
class Texture;

class Book
{
public:
	Book(LivingObject* Owner)
	{
		owner = Owner;

		offset = Vector(-50, -50);

		ownTextures = SpriteManager::GetInstance()->GetTextureMap("Book");

		SetBookState("Idle");
	}
	~Book() = default;
	void Update();

	void SetBookState(std::string state);

private:
	Vector pos;
	Vector offset;
	LivingObject* owner;
	std::map<std::string, std::vector<Texture*>>* ownTextures = nullptr;
	Animator animator;
};

