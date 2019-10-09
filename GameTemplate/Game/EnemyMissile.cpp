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

	if (m_player != nullptr) {
		CVector3 toPlayer = m_player->GetPosition() - m_position;
		toPlayer.Normalize();
		CVector3 vec = toPlayer + m_forward;
		vec.Normalize();
		float angle = m_forward.Dot(vec);
		if (angle < 1.0f)
		{
			float dir = m_up.Dot(vec);

			CVector3 axis;
			axis.Cross(m_forward, vec);
			axis = axis * dir;
			axis.Normalize();
			CQuaternion qRot;
			float deg = CMath::RadToDeg(AcosWrapper(angle));
			qRot.SetRotationDeg(axis, 5.0f * deg * GameTime().GetFrameDeltaTime());
			m_rotation.Multiply(qRot);
		}
	}
	AxisUpdate();

	m_moveSpeed = m_forward * 10000.0f * GameTime().GetFrameDeltaTime();

	m_position += m_moveSpeed;

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void EnemyMissile::AxisUpdate()
{
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward = { mRot.m[2][0],mRot.m[2][1] ,mRot.m[2][2] };
	m_right = { mRot.m[0][0],mRot.m[0][1] ,mRot.m[0][2] };
	m_up = { mRot.m[1][0],mRot.m[1][1] ,mRot.m[1][2] };
	m_forward.Normalize();
	m_right.Normalize();
	m_up.Normalize();
}
