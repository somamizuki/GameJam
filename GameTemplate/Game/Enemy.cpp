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
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/ui_TargetLock.dds",
	//	75.0f,
	//	75.0f,
	//	false
	////);
	//m_spriteRender->SetScale(m_UiScale);
	//m_spriteRender->SetPosition(m_UiPosition);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);		//スキンモデルレンダー
	m_skinModelRender->Init(L"modelData/Enemy.cmo");									//表示したいモデルのパス
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	//skinModelRender->SetShadowCasterFlag(true);					//モデルの影を描画

//	m_effect = NewGO<prefab::CEffect>(0);
//	m_effect->Play(L"effect/MissileSmoke.efk");
	CVector3 effectScale = CVector3::One * 100.0f;
	//m_effect->SetScale(effectScale);

	m_player = FindGO<Player>("player");
	return true;
}

void Enemy::Update()
{
	GetPlayerInfo();
	EnemyMovement();
	PlayEffect();
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void Enemy::OnDestroy()
{
	DeleteGO(m_skinModelRender);		//skinModelRenderをdelete
	//DeleteGO(m_effect);
}

void Enemy::GetPlayerInfo()
{
	if (m_player != nullptr) {
		m_playerInfo.Forward = m_player->GetForward();
		m_playerInfo.Position = m_player->GetPosition();
		m_playerInfo.Right = m_player->GetRight();
		m_playerInfo.Up = m_player->GetUp();
	}

}

void Enemy::EnemyMovement()
{
	AxisUpdate();
	CVector3 Target = m_playerInfo.Position;

	if (m_position.y < 5000.0f)
	{
		Target += CVector3::AxisY * 1000000.0f;
		m_speed = min(MAX_SPEED, (m_position.y));

	}
	else
	{
		m_speed = min(MAX_SPEED, m_speed + 10000.0f * GameTime().GetFrameDeltaTime());
	}

	m_moveSpeed = CVector3::Zero;
	const float ROLL_SPEED = 200.0f;
	const float PITCH_SPEED = 100.0f;
	AxisUpdate();
	CVector3 vec = CVector3::Zero;
	CVector3 toTarget = Target - m_position;
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
	qRot.SetRotationDeg(m_forward, ROLL_SPEED * -dir * GameTime().GetFrameDeltaTime());
	m_rotation.Multiply(qRot);
	AxisUpdate();

	vec = CVector3::Zero;
	dotresult = toTarget.Dot(m_up);
	vec += m_up * dotresult;
	dotresult = toTarget.Dot(m_forward);
	vec += m_forward * dotresult;
	vec.Normalize();

	dir = vec.Dot(m_up);
	qRot.SetRotationDeg(m_right, PITCH_SPEED * -dir * GameTime().GetFrameDeltaTime());
	m_rotation.Multiply(qRot);
	AxisUpdate();


	m_moveSpeed += m_forward * m_speed;
	m_position += m_moveSpeed * GameTime().GetFrameDeltaTime();
}

void Enemy::PlayEffect()
{
	//if (!(isEffectPlay))
	//{
	//	m_effect = NewGO<prefab::CEffect>(0);
	//	m_effect->Play(L"effect/MissileSmoke.efk");
	//	CVector3 effectScale = CVector3::One * 100.0f;
	//	m_effect->SetScale(effectScale);
	//}
	//if (m_effect != nullptr) {
	//	CVector3 effectPos = m_position;
	//	effectPos -= m_forward * 750.0f;
	//	//isEffectPlay = m_effect->IsPlay();
	//	m_effect->SetPosition(effectPos);
	//	m_effect->SetRotation(m_rotation);
	//}
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

void Enemy::EnemyUi()
{

}
