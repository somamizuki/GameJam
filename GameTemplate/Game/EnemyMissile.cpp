#include "stdafx.h"
#include "EnemyMissile.h"

EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
}

bool EnemyMissile::Start()
{
	m_position.Set(0, 100.0f, -500.0f);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	
	return true;
}

void EnemyMissile::Update()
{


	m_skinModelRender->SetPosition(m_position);
}
