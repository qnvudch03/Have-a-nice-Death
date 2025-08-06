#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "UI.h"
#include "InputManager.h"
//Todo ���� ĳ���ͷ� �ٲ����
//#include "Actor.h"


void Scene::Init()
{
	// �ʿ��� ���ҽ� �ε�
	loadResource();
	loadUI();
}

void Scene::Destroy()
{
	//���ν� ������ ������ ResourecManager���� �����Ѵ�.
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
	// ����� ��ü�� �߰�
	for (auto& actor : _reserveAdd)
	{
		addActor(actor);
	}
	_reserveAdd.clear();


	// ����� ��ü�� ����, A Enemy 2��
	for (auto actor : _reserveRemove)
	{
		removeActor(actor);	// ��¥ �޸𸮸� ����
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

	//UI�� �� �׸� �� �� ��������
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

	// ���� �����ϴ� _actor �����̳ʿ� �ٷ� �����ʴ´�.
	// Update �������� _actor �����̳ʸ� ��ȸ���ϼ��� �ֱ⶧����
	// �����ϰ� ����ϱ� ���ؼ� ���� �ý����� ����Ѵ�.
	_actors.insert(actor);

	// ������ ������ �°�, ������ �����̳ʵ� ä���ش�.
	if (actor->GetRenderLayer() == RenderLayer::Max)
		return;

	_renderList[(int32)actor->GetRenderLayer()].push_back(actor);
}

void Scene::removeActor(Object* actor)
{
	//// ������ ����Ʈ���� ����
	//if (actor->GetRenderLayer() != RenderLayer::Count)
	//{
	//	auto it = _renderList[(int32)actor->GetRenderLayer()].find(actor);
	//	if (it != _renderList[(int32)actor->GetRenderLayer()].end())
	//	{
	//		_renderList[(int32)actor->GetRenderLayer()].erase(it);
	//	}
	//}

	//// ��¥ �޸� ����
	//{
	//	auto it = _actors.find(actor);
	//	if (it != _actors.end())
	//	{
	//		// ������ �����ϴ� �����̳ʿ����� ���� ���� (������Ʈ Ǯ or new )
	//		_actors.erase(it);
	//		actor->Destroy();
	//		// new ������� ��ü
	//		delete actor;	// �޸� ����
	//	}
	//}
}
