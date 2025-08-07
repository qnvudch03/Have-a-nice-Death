#pragma once

class GameScene;
class Object;

class Stage
{
public:
	Stage(GameScene* Iscene) { gameScene = Iscene; }
	~Stage();

	bool LoadStage(std::string stage);

	bool LoadStageInfo(std::string stage);

private:

	std::vector< Object*> stageObjectVec;

	GameScene* gameScene = nullptr;
	std::string currentStage;
};

