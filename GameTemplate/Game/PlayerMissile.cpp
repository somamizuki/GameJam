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
		minimissile.m_toMiniMissileDist = vec.Length();
		vec.Normalize();
		minimissile.m_toMiniMissile = vec;
	}
	return true;
}

void PlayerMissile::Update()
{

	if (m_isFire)
	{
		if (m_enemy&& !m_enemy->IsDead())Homing();
		AxisUpdate();

		m_moveSpeed = m_forward * m_speed * GameTime().GetFrameDeltaTime();

		m_position += m_moveSpeed;
		for (auto& minimissile : m_sMiniMissileArray)
		{
			CMatrix mRot;
			mRot.MakeRotationFromQuaternion(minimissile.m_rotation);
			minimissile.m_right = { mRot.m[0][0],mRot.m[0][1],mRot.m[0][2] };
			minimissile.m_up = { mRot.m[1][0],mRot.m[1][1],mRot.m[1][2] };
			minimissile.m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
			minimissile.m_right.Normalize();
			minimissile.m_up.Normalize();
			minimissile.m_forward.Normalize();
			if (m_enemy && !m_enemy->IsDead())
			{
				CVector3 toEnemy = m_enemy->GetPosition() - m_position;
				if (toEnemy.Length() < 1000.0f)
				{
					DeleteGO(m_enemy);
					DeleteGO(this);
				}
				minimissile.m_toMiniMissileDist = min(minimissile.m_toMiniMissileDist + 10000.0f * GameTime().GetFrameDeltaTime(), toEnemy.Length());
			}
			

			CVector3 vec = m_right * minimissile.m_toMiniMissile.x + m_up * minimissile.m_toMiniMissile.y + m_forward * minimissile.m_toMiniMissile.z;
			vec.Normalize();
			CVector3 toNextPos = minimissile.m_position;
			minimissile.m_position = m_position + vec * minimissile.m_toMiniMissileDist;
			toNextPos = minimissile.m_position - toNextPos;
			toNextPos.Normalize();

			float angle = minimissile.m_forward.Dot(toNextPos);
			if (angle < 1.0f) {

				CVector3 axis;
				axis.Cross(minimissile.m_forward, toNextPos);
				axis.Normalize();
				CQuaternion qRot;
				float deg = CMath::RadToDeg(AcosWrapper(angle));
				qRot.SetRotationDeg(axis, deg);
				minimissile.m_rotation.Multiply(qRot);
			}
			mRot;
			mRot.MakeRotationFromQuaternion(minimissile.m_rotation);
			minimissile.m_right = { mRot.m[0][0],mRot.m[0][1],mRot.m[0][2] };
			minimissile.m_up = { mRot.m[1][0],mRot.m[1][1],mRot.m[1][2] };
			minimissile.m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
			minimissile.m_right.Normalize();
			minimissile.m_up.Normalize();
			minimissile.m_forward.Normalize();



			minimissile.m_skinModel->SetPosition(minimissile.m_position);
			minimissile.m_skinModel->SetRotation(minimissile.m_rotation);

		}
		m_speed = min(MAX_SPEED, m_speed + 5000.0f * GameTime().GetFrameDeltaTime());
		m_timer += 1.0f * GameTime().GetFrameDeltaTime();

		if (m_timer > 5.0f)
		{
			DeleteGO(this);
		}
	}


	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

}

void PlayerMissile::OnDestroy()
{
	for (auto& minimissile : m_sMiniMissileArray)
	{
		DeleteGO(minimissile.m_skinModel);
	}
	DeleteGO(m_skinModelRender);
}

void PlayerMissile::Homing()
{
	


	AxisUpdate();
	CVector3 toEnemy = m_enemy->GetPosition() - m_position;
	toEnemy.Normalize();
	CVector3 vec = toEnemy;
	vec.Normalize();
	float angle = m_forward.Dot(vec);
	if (angle < 1.0f) {

		CVector3 axis;
		axis.Cross(m_forward, vec);
		axis.Normalize();
		CQuaternion qRot;
		float deg = CMath::RadToDeg(AcosWrapper(angle));
		qRot.SetRotationDeg(axis, 5.0f * deg * GameTime().GetFrameDeltaTime());
		m_rotation.Multiply(qRot);
		AxisUpdate();
	}
	angle = m_forward.Dot(toEnemy);
	if (angle < 0.0f)
	{
		m_enemy = nullptr;
	}
}
