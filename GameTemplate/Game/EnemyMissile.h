#pragma once
#include "MissileBase.h"

class EnemyMissile :public MissileBase
{
public:
	EnemyMissile();
	~EnemyMissile();
	bool Start();
	void Update();
private:
	CVector3* playerPos;
	CVector3 m_moveSpeed;
};

