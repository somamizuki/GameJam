#pragma once
class Player;
class HPbar : public IGameObject
{
public:
	HPbar();
	~HPbar();
	bool Start();
	void Update();
	void MainBar();
	void BarBack();

private:
	void ReduceHpBar();

	Player* m_player = nullptr;
	prefab::CSpriteRender* m_sprite = nullptr;
	prefab::CSpriteRender* m_backsprite = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_backPos = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
};

