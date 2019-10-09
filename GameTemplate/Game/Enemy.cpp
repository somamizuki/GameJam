#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	
}

bool Enemy::Start()
{

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);		//スキンモデルレンダー
	//skinModelRender->Init(L"");									//表示したいモデルのパス
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	//skinModelRender->SetShadowCasterFlag(true);					//モデルの影を描画

	m_player = FindGO<Player>("player");
	return true;
}

void Enemy::Update()
{
	GetPlayerInfo();

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void Enemy::OnDestroy()
{
	DeleteGO(m_skinModelRender);		//skinModelRenderをdelete
}

void Enemy::GetPlayerInfo()
{
	if (m_player!=nullptr) {
		m_playerInfo.Forward = m_player->GetForward();
		m_playerInfo.Position = m_player->GetPosition();
		m_playerInfo.Right = m_player->GetRight();
		m_playerInfo.Up = m_player->GetUp();
	}
	
}

void Enemy::EnemyMovement()
{
	const float ROT_SPEED = 300.0f;

	AxisUpdate();
	CVector3 vec = CVector3::Zero;

	CVector3 target = CVector3::Zero;
	target.y = 5000.0f;
	CVector3 toTarget = target - m_playerInfo.Position;
	toTarget.Normalize();
	float dotresult = toTarget.Dot(m_up);
	vec += m_up * dotresult;
	dotresult = toTarget.Dot(m_right);
	vec += m_right * dotresult;
	vec.Normalize();
	dotresult = vec.Dot(m_up);
	float dir = 0.0f;
	dir = vec.Dot(m_right);
	CQuaternion qRot;
	qRot.SetRotationDeg(m_forward, ROT_SPEED * -dir*GameTime().GetFrameDeltaTime());
	m_rotation.Multiply(qRot);
	AxisUpdate();
	dir = vec.Dot(m_right);
	qRot.SetRotationDeg(m_right, ROT_SPEED * -dir * GameTime().GetFrameDeltaTime());
	m_rotation.Multiply(qRot);
	AxisUpdate();
	m_moveSpeed += m_forward * 10000.0f;
}

void Enemy::FollowPlayer()
{

}

void Enemy::AxisUpdate()
{
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_right = { mRot.m[0][0],mRot.m[0][1],mRot.m[0][2] };
	m_up = { mRot.m[1][0],mRot.m[1][1],mRot.m[1][2] };
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();
}
