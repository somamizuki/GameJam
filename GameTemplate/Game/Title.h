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
	prefab::CSpriteRender* m_pressA = nullptr;

	CVector3 m_position;
	CVector3 m_scale;
	CVector4 m_mulColor = CVector4::White;
	bool m_isGameStart = false;
};

