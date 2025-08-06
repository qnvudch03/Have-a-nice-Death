#pragma once

class GameScene;

class Stage
{
public:
	Stage(GameScene* Iscene) { gamescene = Iscene; }
	~Stage()
	{

	}

	void LoadStage(std::string stage);

private:
	GameScene* gamescene = nullptr;
	std::string currentStage;
};

