#pragma once

class PlayerMissile;

class MissileGauge : public IGameObject
{
public:
	MissileGauge();
	~MissileGauge();
	bool Start();
	void Update();

private:
	PlayerMissile* m_missile;

	prefab::CSpriteRender* m_back = nullptr;	//�Q�[�W�̔w�i�B
	CVector3 m_backPos = CVector3::Zero;
	prefab::CSpriteRender* m_gauge = nullptr;	//�Q�[�W�B
	CVector3 m_gaugePos = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
};

