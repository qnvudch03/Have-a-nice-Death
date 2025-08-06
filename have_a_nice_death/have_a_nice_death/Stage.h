#pragma once

class Scene;
class Object;

class Stage
{
public:
	Stage(Scene* Iscene) { scene = Iscene; }
	~Stage();

	bool LoadStage(std::string stage);

	bool LoadStageInfo(std::string stage);

private:

	std::vector< Object*> stageObjectVec;

	Scene* scene = nullptr;
	std::string currentStage;
};

