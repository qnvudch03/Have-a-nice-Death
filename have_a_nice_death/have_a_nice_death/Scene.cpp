#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "UI.h"
#include "InputManager.h"
#include "Game.h"
#include "DebugLenderer.h"
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
	if (canObjectUpdate)
	{
		for (auto actor : _actors)
		{
			actor->Update(deltatTime);
		}
	}

	if (SceneUI != nullptr)
	{
		for (auto& ui : *SceneUI)
		{
			ui->Update(deltatTime);
		}
	}
	

	if (InputManager::GetInstance()->GetButtonDown(KeyType::F1))
	{
		IsDbugMode = !IsDbugMode;

		for (auto& list : _renderList)
		{
			for (auto actor : list)
			{
				actor->SetDebugMode(IsDbugMode);
			}
		}
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
	for (auto& actor : _reserveRemove)
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
			//actor->SetDebugMode(debugMode);
			actor->Render(renderTarget);
		}
	}

	if (IsDbugMode)
	{
		Game::GetInstance()->GetDebugLenderer()->DrawReserved();
	}

	//UI�� �� �׸� �� �� ��������
	if (SceneUI == nullptr)
		return;

	for (auto& ui : *SceneUI)
	{
		if (!ui->IsOpen())
			continue;

		ui->Render(renderTarget);
	}


}

void Scene::EraseScene()
{
	for (auto Iter : *SceneUI)
	{
		Iter->Close();
	}
}

void Scene::ReserveRemove(Object* actor)
{
	_reserveRemove.push_back(actor);

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

UI* Scene::GetUIByName(std::string name)
{
	for (auto& Iter : *SceneUI)
	{
		if (!Iter->_name.compare(name))
			return Iter;

	}
	return nullptr;
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

	//_renderList[(int32)actor->GetRenderLayer()].push_back(actor);
	_renderList[(int32)actor->GetRenderLayer()].insert(actor);
}

void Scene::removeActor(Object* actor)
{
	// ������ ����Ʈ���� ����
	if (actor->GetRenderLayer() != RenderLayer::Max)
	{
		auto it = _renderList[(int32)actor->GetRenderLayer()].find(actor);
		if (it != _renderList[(int32)actor->GetRenderLayer()].end())
		{
			_renderList[(int32)actor->GetRenderLayer()].erase(it);
		}
	}

	// ��¥ �޸� ����
	{
		auto it = _actors.find(actor);
		if (it != _actors.end())
		{
			// ������ �����ϴ� �����̳ʿ����� ���� ���� (������Ʈ Ǯ or new )
			_actors.erase(it);
			actor->Destroy();
			// new ������� ��ü
			delete actor;	// �޸� ����
		}
	}
}
