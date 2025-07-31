#pragma once
#include "Singleton.h"

class Scene;
class UI;

class UIManager : public Singleton<UIManager>
{
public:
	void Init(fs::path directory);
	void Update(Scene* scene);

	void Destroy();

	void OnMouseButtonClicked(Vector pos);

	std::vector<UI*>* GetSceneUI(Scene* scene);

private:

	void CreateUIVec(fs::path directory);

	std::map<std::string, std::vector<UI*>> _gameUI;
};

