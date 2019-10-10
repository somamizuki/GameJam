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
	void Homing();
	
	Player* m_player = nullptr;
	bool m_enableHoming = false;
};

