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

	//Enemy�̃|�C���^���Z�b�g�B
	void SetEnemy(Enemy* enemy) {
		m_enemy = enemy;
	}
private:
	void AxisUpdate();
	Enemy* m_enemy = nullptr;

};

