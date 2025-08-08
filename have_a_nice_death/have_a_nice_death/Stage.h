#pragma once

class GameScene;
class Object;
class LivingObject;

class Stage
{
public:
	Stage(GameScene* Iscene) { gameScene = Iscene; }
	~Stage();

	bool LoadStage(std::string stage);

	bool LoadStageInfo(std::string stage);

private:

	std::vector< Object*> stageObjectVec;

	LivingObject* MakeCharacter(std::string type);

	GameScene* gameScene = nullptr;
	std::string currentStage;
};

