#pragma once

class Object;
class UI;

class Scene
{
public:
	virtual void Init();
	virtual void Destroy();
	virtual void Update(float deltatTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);


	// Actor Remove
	void ReserveRemove(Object* actor);
	void ReserveAdd(Object* actor);

	void RemoveAllActor();

protected:
	virtual void loadResource() {}
	virtual void loadUI() {}

private:
	void addActor(Object* actor);
	void removeActor(Object* actor);

protected:

	// ������Ʈ �� ���� �����̳�
	std::unordered_set<Object*> _actors;	// ���� ��ü�� �ִ� ����

	// ������ ������ �����ϱ����� �����̳�
	std::vector<Object*> _renderList[RenderLayer::Max];

	// �߰� ������ ���͵��� ����
	std::vector<Object*> _reserveAdd;		// �߰��Ǿ�� �ϴ� ���͵��� ����
	std::vector<Object*> _reserveRemove;	// �����Ǿ�� �ϴ� ���͵��� ����

	//UIManager _ui;
	std::vector<UI*>* SceneUI;
};

