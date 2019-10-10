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
	void Fire(float speed)
	{
		m_isFire = true;
		m_speed = speed;
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
	std::vector<SMiniMissile> m_sMiniMissileArray;
	bool m_isFire = false;
	float m_speed = 0.0f;
	float m_timer = 0.0f;
	const float MAX_SPEED = 20000.0f;
};

