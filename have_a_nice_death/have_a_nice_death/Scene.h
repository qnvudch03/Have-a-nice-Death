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

	// 업데이트 용 접근 컨테이너
	std::unordered_set<Object*> _actors;	// 원본 객체가 있는 개념

	// 렌더링 순서를 보장하기위한 컨테이너
	std::vector<Object*> _renderList[RenderLayer::Max];

	// 추가 예정인 액터들을 관리
	std::vector<Object*> _reserveAdd;		// 추가되어야 하는 액터들을 관리
	std::vector<Object*> _reserveRemove;	// 삭제되어야 하는 액터들을 관리

	//UIManager _ui;
	std::vector<UI*>* SceneUI;
};

