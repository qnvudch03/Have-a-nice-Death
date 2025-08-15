#pragma once

class GameScene;
class Object;
class LivingObject;
class StaticObject;
class UI;

class Stage
{
public:
	Stage(GameScene* Iscene) { gameScene = Iscene; }
	~Stage();

	bool LoadStage(std::string stage);

	bool LoadStageInfo(std::string stage);

	void Update();

private:

	int TotalEnemy = 0;
	int MonsterCounter = 0;
	int WaveCount = 0;
	std::vector<int> WaveMonstercount;

	std::vector<int> divideIntoThree(int totalEnemy);

	std::vector< Object*> stagePreloadObjectVec;
	std::vector<Object*> stageLivingObjectVec;
	std::vector< Object*> stageStaticObjectVec;

	LivingObject* MakeCharacter(std::string type, Vector pos = Vector(0,0));

	void SetReady(Object* obj);

	GameScene* gameScene = nullptr;
	//std::string currentStage;

	bool bIsStageReady = false;

	void playerDie();
	void playerHitted();

	void enemyDie();

	LivingObject* player = nullptr;

	void StartStage();
	void StartWave();
	void StageClear();

	UI* hpBar = nullptr;
};

