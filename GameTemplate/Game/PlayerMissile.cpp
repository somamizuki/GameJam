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
	m_skinModelRender->Init(L"modelData/NormalMissile.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	int i = 0;
	CVector3 npos;
	m_level.Init(L"level/PlayerMissile.tkl", [&](LevelObjectData& objectdata) {
		if (std::wcscmp(objectdata.name, L"NormalMissile") == 0)
		{
			npos = objectdata.position;
		}
		else if (std::wcscmp(objectdata.name, L"MiniMissile") == 0)
		{
			SMiniMissile minimissile;
			minimissile.m_position = objectdata.position;
			m_sMiniMissileArray.push_back(minimissile);


		}
		return true;
	});

	for (auto& minimissile : m_sMiniMissileArray)
	{
		minimissile.m_skinModel = NewGO<prefab::CSkinModelRender>(0);
		minimissile.m_skinModel->Init(L"modelData/MiniMissile.cmo");
		CVector3 vec = minimissile.m_position - npos;
		minimissile.m_toNormalMissileDist = vec.Length();
		vec.Normalize();
		minimissile.m_toNormalMissile = vec;
	}
	return true;
}

void PlayerMissile::Update()
{
	
	if (m_isFire)
	{
		Homing();
	}
	else
	{
		for (auto& minimissile : m_sMiniMissileArray)
		{
			CVector3 vec = m_forward * m_forward.Dot(minimissile.m_toNormalMissile) + m_right * m_right.Dot(minimissile.m_toNormalMissile) + m_up * m_up.Dot(minimissile.m_toNormalMissile);
			vec.Normalize();
			minimissile.m_position = m_position + vec * minimissile.m_toNormalMissileDist;
			minimissile.m_rotation = m_rotation;
			minimissile.m_skinModel->SetPosition(minimissile.m_position);
			m_skinModelRender->SetRotation(minimissile.m_rotation);

		}
	}
	

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void PlayerMissile::Homing()
{
	AxisUpdate();

	if (m_enemy != nullptr) {
		CVector3 toEnemy = m_enemy->GetPosition() - m_position;
		toEnemy.Normalize();
		CVector3 vec = toEnemy + m_forward;
		vec.Normalize();
		float angle = m_forward.Dot(vec);
		if (angle < 1.0f) {
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

	m_moveSpeed = m_forward * 1000.0f * GameTime().GetFrameDeltaTime();

	m_position += m_moveSpeed;
	for (auto& minimissile : m_sMiniMissileArray)
	{
		CVector3 vec = m_forward * m_forward.Dot(minimissile.m_toNormalMissile) + m_right * m_right.Dot(minimissile.m_toNormalMissile) + m_up * m_up.Dot(minimissile.m_toNormalMissile);
		vec.Normalize();
		minimissile.m_position = m_position + vec * minimissile.m_toNormalMissileDist;
		minimissile.m_rotation = m_rotation;
		minimissile.m_skinModel->SetPosition(minimissile.m_position);
		m_skinModelRender->SetRotation(minimissile.m_rotation);

	}
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
