#include "pch.h"
#include "Sensor.h"
#include "Game.h"
#include "Scene.h"
#include "Object.h"
#include "GameScene.h"
#include "Collider.h"
#include "LivingObject.h"

void Sensor::Update(Vector textureSize)
{
	//위치 변환
	Vector actorPos = owner->collider->GetCenterPos();
	Vector colliderSize = owner->collider->GetSize();

	//텍스쳐 사이즈 사용 차단
	textureSize.x = 0;
	textureSize.y = 0;

	switch (sensorType)
	{
	case WallSensor:
		pos.x = actorPos.x + ( colliderSize.x * 0.6f * owner->forwordDirection );
		pos.y = actorPos.y;
		break;

	case GroundSensor:
		pos.x = actorPos.x;
		pos.y = actorPos.y + colliderSize.y * 0.6;
		break;

	case CornerSensor:
		pos.x = actorPos.x + (colliderSize.x * 0.8 * owner->forwordDirection);
		pos.y = actorPos.y + colliderSize.y * 0.6f;
		break;
	case SensorMax:
		break;
	default:
		break;
	}

	{
		recPos.TopLeft.x = pos.x - size.x * 0.5f;
		recPos.TopLeft.y = pos.y - size.y * 0.5f;

		recPos.TopRight.x = pos.x + size.x * 0.5f;
		recPos.TopRight.y = pos.y - size.y * 0.5f;

		recPos.BottomLeft.x = pos.x - size.x * 0.5f;
		recPos.BottomLeft.y = pos.y + size.y * 0.5f;

		recPos.BottomRight.x = pos.x + size.x * 0.5f;
		recPos.BottomRight.y = pos.y + size.y * 0.5f;
	}
	
	CheckActive();
}

void Sensor::CheckActive()
{
	GameScene* CurrentGameScene = static_cast<GameScene*>(Game::GetInstance()->GetCurrentScence());
	std::unordered_set<Object*>* actors = CurrentGameScene->GetActors();

	for (auto& actor : *actors)
	{
		if (actor->GetRenderLayer() != RenderLayer::Platform)
			continue;

		RectanglePos actorRect = actor->collider->Getrectangle();

		if (sensorType == SensorType::GroundSensor)
		{
			float margin = 30.0f;

			isActive =
				(recPos.TopLeft.x >= actorRect.TopLeft.x - margin && recPos.TopLeft.y >= actorRect.TopLeft.y) &&
				(recPos.TopRight.x <= actorRect.TopRight.x + margin && recPos.TopRight.y >= actorRect.TopRight.y) &&
				(recPos.BottomLeft.x >= actorRect.BottomLeft.x - margin && recPos.BottomLeft.y <= actorRect.BottomLeft.y) &&
				(recPos.BottomRight.x <= actorRect.BottomRight.x + margin && recPos.BottomRight.y <= actorRect.BottomRight.y);

			if (isActive == true)
				return;
		}

		else if (sensorType == SensorType::WallSensor)
		{
			isActive =
				(recPos.TopLeft.x >= actorRect.TopLeft.x && recPos.TopLeft.y >= actorRect.TopLeft.y) &&
				(recPos.TopRight.x <= actorRect.TopRight.x && recPos.TopRight.y >= actorRect.TopRight.y) &&
				(recPos.BottomLeft.x >= actorRect.BottomLeft.x && recPos.BottomLeft.y <= actorRect.BottomLeft.y) &&
				(recPos.BottomRight.x <= actorRect.BottomRight.x && recPos.BottomRight.y <= actorRect.BottomRight.y);

			if (isActive == true)
				return;
		}

		
	}
}
