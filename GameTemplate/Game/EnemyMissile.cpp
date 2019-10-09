#include "stdafx.h"
#include "EnemyMissile.h"
#include "Player.h"

EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
	DeleteGO(m_skinModelRender);
}

bool EnemyMissile::Start()
{
	m_player = FindGO<Player>("player");

	m_position.Set(0, 100.0f, -500.0f);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	
	return true;
}

void EnemyMissile::Update()
{
	if (m_player != nullptr) {
		CVector3 toPos = m_player->GetPosition() - m_position;
		toPos.Normalize();
		CVector3 moveNom = m_moveSpeed;
		moveNom.Normalize();
		
	}

	m_position += m_moveSpeed;

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}
