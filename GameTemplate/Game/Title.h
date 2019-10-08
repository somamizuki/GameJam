#pragma once
class Title :public IGameObject
{
public:
	Title() {}
	~Title() {}
	bool Start();
	void Update();
	void OnDestroy();
private:
	prefab::CSpriteRender* m_sprite = nullptr;
	CVector4 m_mulColor = CVector4::White;
	bool m_isGameStart = false;
};

