#include "pch.h"
#include "InteractableObject.h"
#include "Game.h"
#include "GameScene.h"
#include "Collider.h"
#include "LivingObject.h"
#include "InputManager.h"

InteractableObject::InteractableObject(RenderLayer rendertype, ImageAnchor drawanchor, Vector Pos) : Super(rendertype, drawanchor)
{
	SetPos(Pos);

	gameScene = Game::GetGameScene();
	player = gameScene->GetStage()->GetPlayer();


	animator.onAnimEnd = [this]() {this->OnAnimEnd(); };
}

void InteractableObject::Update(float deltaTime)
{
	Super::Update(deltaTime);


	if (!readyToInteract)
		return;

	activate = false;

	/*RectanglePos playerCollider = player->collider->Getrectangle();
	Vector TopLeft = playerCollider.TopLeft;
	Vector BottomRight = playerCollider.BottomRight;*/

	Vector playerPos = player->collider->GetCenterPos();

	Vector textureSize = animator.GetAnimTexture()->GetTextureSize();
	Vector pos = GetPos();


	if (playerPos.x >= pos.x - textureSize.x * 0.5 &&
		playerPos.y >= pos.y - textureSize.y * 0.5 &&

		playerPos.x <= pos.x + textureSize.x * 0.5 &&
		playerPos.y <= pos.y + textureSize.y * 0.5)

	{
		activate = true;
	}

	if (activate)
	{
		if (InputManager::GetInstance()->GetButtonDown(KeyType::E))
		{
			DoInteract();
		}
	}
}

void InteractableObject::SetDebugMode(bool debugmode)
{

}
