#pragma once

class EditorScene;
class Game;

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

private:
	bool Activate = false;
	EditorScene* editScene = nullptr;
	Game* game = nullptr;
};

