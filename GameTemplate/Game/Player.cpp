#include "stdafx.h"
#include "Player.h"
#include "PlayerMissile.h"
#include "Enemy.h"
#include "GameStage.h"

namespace {
	const float MAX_SPEED = 20000.0f;
	const float ACCELERATION = 100.0f;
	const float DEFAULT_SPEED = 5000.0f;
	const float ROLL_SPEED = 200.0f;
	const float PITCH_SPEED = 100.0f;
	const float YAW_SPEED = 20.0f;
}

Player::Player()
{
}
Player::~Player()
{
}
bool Player::Start()
{
	m_characon.Init(500.0f, 500.0f, m_position);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/StarSparrow.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_normalSRV.CreateFromDDSTextureFromFile(L"modelData/StarSparrow_Normal.dds");
	m_specSRV.CreateFromDDSTextureFromFile(L"modelData/spec.dds");
	m_skinModelRender->FindMaterial([&](auto material) {
		material->SetNormalMap(m_normalSRV.GetBody());
		material->SetSpecularMap(m_specSRV.GetBody());
	});
	CVector3 ppos;
	CVector3 mpos;
	m_level.Init(L"level/PlayerMissilePos.tkl", [&](LevelObjectData& objectdata) {
		if (std::wcscmp(objectdata.name, L"NormalMissile") == 0)
		{
			mpos = objectdata.position;
		}
		else if (std::wcscmp(objectdata.name, L"StarSparrow") == 0)
		{
			ppos = objectdata.position;
		}
		return true;
	});
	m_tomissilePos = mpos - ppos;
	m_stage = FindGO<GameStage>("stage");

	return true;
}

void Player::Update()
{
	AxisUpdate();
	Movement();
	MissileManager();
	Execute();
}

void Player::Execute()
{

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void Player::Movement()
{
	float PadInput_LX = -Pad(0).GetLStickXF();
	float PadInput_LY = Pad(0).GetLStickYF();
	bool PadInput_RT = Pad(0).IsPress(enButtonRB2);
	bool PadInput_LT = Pad(0).IsPress(enButtonLB2);
	bool PadInput_RB = Pad(0).IsPress(enButtonRB1);
	bool PadInput_LB = Pad(0).IsPress(enButtonLB1);
	float DeltaTime = GameTime().GetFrameDeltaTime();
	m_moveSpeed = CVector3::Zero;
	if (PadInput_RT) m_speed = min(MAX_SPEED, m_speed + ACCELERATION);
	if (!PadInput_RT) m_speed = min(max(0.0f, m_speed - ACCELERATION), m_speed + ACCELERATION);
	m_moveSpeed += m_forward * m_speed;

	CQuaternion qRot;
	qRot.SetRotationDeg(m_forward, PadInput_LX * ROLL_SPEED * DeltaTime);
	m_rotation.Multiply(qRot);
	AxisUpdate();
	qRot.SetRotationDeg(m_right, PadInput_LY * PITCH_SPEED * DeltaTime);
	m_rotation.Multiply(qRot);
	AxisUpdate();
	if (PadInput_RB)
	{
		qRot.SetRotationDeg(m_up, YAW_SPEED * DeltaTime);
		m_rotation.Multiply(qRot);
		AxisUpdate();
	}
	if (PadInput_LB)
	{
		qRot.SetRotationDeg(m_up, -YAW_SPEED * DeltaTime);
		m_rotation.Multiply(qRot);
		AxisUpdate();
	}
	m_position = m_characon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
}

void Player::AxisUpdate()
{
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward = { mRot.m[2][0], mRot.m[2][1] ,mRot.m[2][2] };
	m_right = { mRot.m[0][0], mRot.m[0][1] ,mRot.m[0][2] };
	m_up = { mRot.m[1][0], mRot.m[1][1] ,mRot.m[1][2] };
	m_forward.Normalize();
	m_right.Normalize();
	m_up.Normalize();
}

void Player::MissileManager()
{

	if (!m_missile)
	{
		m_missile = NewGO<PlayerMissile>(0);
	}
	else
	{
		AxisUpdate();
		CVector3 vec = m_right * m_tomissilePos.x + m_up * m_tomissilePos.y + m_forward * m_tomissilePos.z;
		m_missile->SetPosition(m_position + vec);
		m_missile->SetRotation(m_rotation);

		float maxDot = -100.0f;
		for (const auto& enemy : m_stage->GetEnemyArray())
		{
			CVector3 toEnemy = enemy->GetPosition() - m_position;
			toEnemy.Normalize();
			float dotresult = m_forward.Dot(toEnemy);
			if (dotresult < 0.85f)
			{
				continue;
			}
			if (dotresult > maxDot)
			{
				maxDot = dotresult;
				m_missile->SetEnemy(enemy);
			}
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_missile->Fire(m_speed + 5000.0f);
			m_missile = nullptr;
		}
		if (m_missile)m_missile->SetEnemy(nullptr);
	}
}
