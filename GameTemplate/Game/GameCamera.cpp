#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}
GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	//ƒJƒƒ‰‚ðÝ’èB
	if (m_player != nullptr)
	{
		CVector3 toCamVec = m_player->GetForward() * -2000.0f + m_player->GetUp() * 500.0f;
		toCamVec.Normalize();
		toCamVec *= MAX_DIST;
		SetPosition(m_player->GetPosition() + toCamVec);
		SetTarget(m_player->GetPosition()+m_player->GetUp() * 500.0f);
	}
	SetFar(5000000.0f);
	SetNear(10.0f);
	CameraUpdate();

	return true;
}

void GameCamera::Update()
{
	if (m_player != nullptr)
	{
		CVector3 toCamVec = m_player->GetForward() * -2000.0f + m_player->GetUp() * 500.0f;
		toCamVec.Normalize();
		toCamVec *= MAX_DIST;
		SetPosition(m_player->GetPosition() + toCamVec);
		SetTarget(m_player->GetPosition() + m_player->GetUp() * 500.0f);
		SetUp(m_player->GetUp());
		if (m_player->IsDead())
		{
			m_player = nullptr;
		}
	}

	CameraUpdate();
}
