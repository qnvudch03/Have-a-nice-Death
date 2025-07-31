#pragma once
#include "Singleton.h"

class UI;

class UIManager : public Singleton<UIManager>
{
public:
	void Init();
	void Update();

	void OnMouseButtonClicked(Vector pos);

private:
	UI* _UiArray[10];
};

