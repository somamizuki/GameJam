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
	//float ReduceHpBar();

	Player* m_player = nullptr;
	prefab::CSpriteRender* m_sprite = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;

	float reduseHp = 0;
};

