#include "pch.h"
#include "SceneLoader.h"

void SceneLoader::ReserveScene(Scene* loadedScene)
{
	if(loadedScene != nullptr)
		_sceneque.push(loadedScene);
}

bool SceneLoader::IsReserved()
{
	if (_sceneque.empty())
		return false;

	return true;
}

Scene* SceneLoader::GetReservedScene()
{
	if (_sceneque.empty())
		return nullptr;

	Scene* reservedScene = _sceneque.front();
	_sceneque.pop();

	return reservedScene;
}
