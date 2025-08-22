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
	virtual void RenderSubWin() {};
	virtual void EraseScene();
	virtual void OnLeftButtonClicked(Vector clickedPos) {};


	// Actor Remove
	void ReserveRemove(Object* actor);
	void ReserveAdd(Object* actor);

	void RemoveAllActor();

	bool IsDbugMode = false;

	void StopObjectUpdate() { canObjectUpdate = false; }
	void StartObjectUpdate() { canObjectUpdate = true; }

	std::unordered_set<Object*>* GetActors() { return &_actors; }
	UI* GetUIByName(std::string name);

protected:
	virtual void loadResource() {}
	virtual void loadUI() {}

private:
	void addActor(Object* actor);
	void removeActor(Object* actor);

	bool canObjectUpdate = true;

protected:

	// ������Ʈ �� ���� �����̳�
	std::unordered_set<Object*> _actors;	// ���� ��ü�� �ִ� ����

	// ������ ������ �����ϱ����� �����̳�
	std::set<Object*> _renderList[RenderLayer::Max];

	// �߰� ������ ���͵��� ����
	std::vector<Object*> _reserveAdd;		// �߰��Ǿ�� �ϴ� ���͵��� ����
	std::vector<Object*> _reserveRemove;	// �����Ǿ�� �ϴ� ���͵��� ����

	//UIManager _ui;
	std::vector<UI*>* SceneUI;
};

