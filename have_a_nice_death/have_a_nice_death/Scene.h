#pragma once

class Scene
{
public:
	virtual void Init();
	virtual void Destroy();
	virtual void Update(float deltatTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);


	// Actor Remove
	void ReserveRemove(class Actor* actor);
	void ReserveAdd(class Actor* actor);

	void RemoveAllActor();

protected:
	virtual void loadResource() {}

private:
	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

protected:
	// �κ�������� ���Ͱ������� ���� �׸��� �׷������Ҽ��� �־
	//std::unordered_set<Actor*> _actors;	// ���� ��ü�� �ִ� ����

	// ������ ������ �����ؼ� �׸��� ����
	std::vector<class Object*> _renderList[RenderLayer::Max];

	// �߰� ������ ���͵��� ����
	//std::vector<Actor*> _reserveAdd;		// �߰��Ǿ�� �ϴ� ���͵��� ����
	//std::vector<Actor*> _reserveRemove;	// �����Ǿ�� �ϴ� ���͵��� ����

	//UIManager _ui;
};

