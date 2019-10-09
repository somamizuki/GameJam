#pragma once
#include "MissileBase.h"

class Player;

class EnemyMissile :public MissileBase
{
public:
	EnemyMissile();
	~EnemyMissile();
	bool Start();
	void Update();
private:
	Player* m_player = nullptr;
	CVector3 m_moveSpeed;
};

