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


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/NormalMissile.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void EnemyMissile::Update()
{
	AxisUpdate();
	if (m_isFire)
	{
		if (m_enableHoming)Homing();
		m_moveSpeed = m_forward * 10000.0f * GameTime().GetFrameDeltaTime();
		m_position += m_moveSpeed;
		m_speed = min(MAX_SPEED, m_speed + 5000.0f * GameTime().GetFrameDeltaTime());
		m_timer += 1.0f * GameTime().GetFrameDeltaTime();

		if (m_timer > 5.0f)
		{
			DeleteGO(m_skinModelRender);
			DeleteGO(this);
		}
	}

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void EnemyMissile::Homing()
{
	AxisUpdate();

	if (m_player != nullptr) {
		CVector3 toPlayer = m_player->GetPosition() - m_position;
		toPlayer.Normalize();
		CVector3 vec = toPlayer + m_forward;
		vec.Normalize();
		float angle = m_forward.Dot(vec);
		if (angle < 1.0f)
		{
			CVector3 axis;
			axis.Cross(m_forward, vec);
			axis.Normalize();
			CQuaternion qRot;
			float deg = CMath::RadToDeg(AcosWrapper(angle));
			qRot.SetRotationDeg(axis, 5.0f * deg * GameTime().GetFrameDeltaTime());
			m_rotation.Multiply(qRot);
			AxisUpdate();
		}
		angle = m_forward.Dot(toPlayer);
		if (angle < 0.0f)
		{
			m_enableHoming = false;
		}
	}
}