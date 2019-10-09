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

	void AxisUpdate();
	Player* m_player = nullptr;
};

