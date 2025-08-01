#pragma once
#include "Scene.h"

class SceneLoader
{
public:
	SceneLoader(){}
	~SceneLoader()
	{
		while (!_sceneque.empty())
		{
			Scene* scene = _sceneque.front();
			_sceneque.pop();

			delete scene;
		}
	}
	void ReserveScene(Scene* loadedScene);
	bool IsReserved();
	Scene* GetReservedScene();

private:
	std::queue<Scene*> _sceneque;
};

