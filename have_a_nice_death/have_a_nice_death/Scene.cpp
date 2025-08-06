#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "UI.h"
#include "InputManager.h"
//Todo 차후 캐릭터로 바꿔야함
//#include "Actor.h"


void Scene::Init()
{
	// 필요한 리소스 로드
	loadResource();
	loadUI();
}

void Scene::Destroy()
{
	//리로스 해제는 무조건 ResourecManager에서 진행한다.
	/*auto a = *SceneUI;

	_reserveAdd.clear();
	_reserveRemove.clear();

	for (auto iter : _actors)
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}
	_actors.clear();

	for (auto iter : *SceneUI)
	{
		SAFE_DELETE(iter);
	}
	SceneUI->clear();*/

}

void Scene::Update(float deltatTime)
{
	for (auto actor : _actors)
	{
		actor->Update(deltatTime);
	}

	if (InputManager::GetInstance()->GetButtonDown(KeyType::F1))
	{
		debugMode != debugMode;
	}

	PostUpdate(deltatTime);

	//_ui.Update();
}

void Scene::PostUpdate(float deltaTime)
{
	// 예약된 객체를 추가
	for (auto& actor : _reserveAdd)
	{
		addActor(actor);
	}
	_reserveAdd.clear();


	// 예약된 객체를 삭제, A Enemy 2번
	for (auto actor : _reserveRemove)
	{
		removeActor(actor);	// 진짜 메모리를 해제
	}
	_reserveRemove.clear();
}

void Scene::Render(ID2D1RenderTarget* renderTarget)
{
	for (auto& list : _renderList)
	{
		for (auto actor : list)
		{
			if (debugMode)
			{
				actor->SetDebugMode(debugMode);
			}

			actor->Render(renderTarget);

		}
	}

	//UI는 다 그린 후 맨 마지막에
	if (SceneUI == nullptr)
		return;

	else
	{
		for (auto& ui : *SceneUI)
		{
			ui->Render(renderTarget);
		}
	}
	
}

void Scene::ReserveRemove(Object* actor)
{
	/*for (auto iter : _reserveRemove)
	{
		if (iter == actor)
			return;
	}

	_reserveRemove.push_back(actor);*/
}

void Scene::ReserveAdd(Object* actor)
{
	//actor->Init();
	_reserveAdd.push_back(actor);
}

void Scene::RemoveAllActor()
{
	/*for (int32 i = 0; i < (int32)RenderLayer::Count; ++i)
	{
		_renderList[i].clear();
	}

	_reserveAdd.clear();
	_reserveRemove.clear();

	for (auto iter : _actors)
	{
		delete iter;
	}
	_actors.clear();*/
}

void Scene::addActor(Object* actor)
{
	//actor->Init();

	// 직접 관리하는 _actor 컨테이너에 바로 넣지않는다.
	// Update 로직에서 _actor 컨테이너를 순회중일수도 있기때문에
	// 안전하게 사용하기 위해서 예약 시스템을 사용한다.
	_actors.insert(actor);

	// 렌더링 순서에 맞게, 렌더링 컨테이너도 채워준다.
	if (actor->GetRenderLayer() == RenderLayer::Max)
		return;

	_renderList[(int32)actor->GetRenderLayer()].push_back(actor);
}

void Scene::removeActor(Object* actor)
{
	//// 렌더링 리스트에서 제거
	//if (actor->GetRenderLayer() != RenderLayer::Count)
	//{
	//	auto it = _renderList[(int32)actor->GetRenderLayer()].find(actor);
	//	if (it != _renderList[(int32)actor->GetRenderLayer()].end())
	//	{
	//		_renderList[(int32)actor->GetRenderLayer()].erase(it);
	//	}
	//}

	//// 진짜 메모리 해제
	//{
	//	auto it = _actors.find(actor);
	//	if (it != _actors.end())
	//	{
	//		// 씬에서 관리하는 컨테이너에서는 제거 가능 (오브젝트 풀 or new )
	//		_actors.erase(it);
	//		actor->Destroy();
	//		// new 만들어진 객체
	//		delete actor;	// 메모리 해제
	//	}
	//}
}
