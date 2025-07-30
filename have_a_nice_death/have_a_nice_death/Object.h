#pragma once

class Texture;

class Object
{
public:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* renderTarget);

	Vector GetPos() { return _pos; }
	void Destory();

private:
	std::vector<Texture*> _OwnTextures;
	Vector _pos = {};
};

