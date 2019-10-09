#pragma once
#include "MissileBase.h"

class Enemy;

class PlayerMissile : public MissileBase
{
public:
	PlayerMissile();
	~PlayerMissile();
	bool Start();
	void Update();

	//Enemyのポインタをセット。
	void SetEnemy(Enemy* enemy) {
		m_enemy = enemy;
	}
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	void Fire()
	{
		m_isFire = true;
	}
private:
	void Homing();
	void AxisUpdate();
	Enemy* m_enemy = nullptr;
	CLevel m_level;
	struct SMiniMissile {
		prefab::CSkinModelRender* m_skinModel = nullptr;
		CVector3 m_toMiniMissile=CVector3::Zero;
		CVector3 m_position=CVector3::Zero;
		CQuaternion m_rotation = CQuaternion::Identity;
		float m_toMiniMissileDist = 0.0f;
	};
	std::vector< SMiniMissile> m_sMiniMissileArray;
	bool m_isFire = true;
};

