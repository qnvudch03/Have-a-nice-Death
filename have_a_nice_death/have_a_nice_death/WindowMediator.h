#pragma once

class EditorScene;
class Game;
class StaticObject;

class WindowMediator
{
	struct CommunicationData
	{
		std::string typd;
		std::string name;
	};

	CommunicationData _communicationData;

public:
	void ReFresh();
	void Update(float deltatime);
	void SetActivate(bool activate) { Activate = activate; }

	void OnSubWinClicked(int witch, Vector pos);
	void OnSubWinNumPressed(int witch);
	void OnMouseWhillMove(bool num);

	StaticObject* GetPreViewObject() { return preViewObject; }

private:
	bool Activate = false;
	EditorScene* editScene = nullptr;
	Game* game = nullptr;

	StaticObject* preViewObject = nullptr;
	StaticObject* MakePreViewObject(std::pair<std::string, std::string> RecievedData);
	void SetCustumAnimSpeed(std::string name, StaticObject* obj);
};

