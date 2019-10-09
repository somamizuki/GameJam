#include "stdafx.h"
#include "PlayerMissile.h"
#include "Enemy.h"

PlayerMissile::PlayerMissile()
{
}

PlayerMissile::~PlayerMissile()
{
}

bool PlayerMissile::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void PlayerMissile::Update()
{
	AxisUpdate();

	if (m_enemy != nullptr) {
		CVector3 toEnemy = m_enemy->GetPosition() - m_position;
		toEnemy.Normalize();
		CVector3 vec = toEnemy + m_forward;
		vec.Normalize();
		float angle = m_forward.Dot(vec);
		if (angle > 1.0) {
			float dir = vec.Dot(m_up);
			CVector3 axis;
			axis.Cross(m_forward, vec);
			axis = axis * dir;
			axis.Normalize();

			CQuaternion qRot;
			qRot.SetRotation(axis, 5.0f * angle * GameTime().GetFrameDeltaTime());
			m_rotation.Multiply(qRot);
		}
	}
	AxisUpdate();

	m_moveSpeed = m_forward * 10000.0f * GameTime().GetFrameDeltaTime();

	m_position += m_moveSpeed;

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void PlayerMissile::AxisUpdate()
{
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_right = { mRot.m[0][0],mRot.m[0][1],mRot.m[0][2] };
	m_up = { mRot.m[1][0],mRot.m[1][1],mRot.m[1][2] };
	m_forward.Normalize();
	m_right.Normalize();
	m_up.Normalize();
}
