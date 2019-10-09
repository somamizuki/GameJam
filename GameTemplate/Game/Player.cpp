#include "stdafx.h"
#include "Player.h"

namespace {
	const float MAX_SPEED = 20000.0f;
	const float ACCELERATION = 100.0f;
	const float DEFAULT_SPEED = 5000.0f;
	const float ROLL_SPEED = 100.0f;
	const float PITCH_SPEED = 80.0f;
}

Player::Player()
{
}
Player::~Player()
{
}
bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/StarSparrow.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Player::Update()
{
	AxisUpdate();
	Movement();

	Execute();
}

void Player::Execute()
{
	m_position += m_moveSpeed * GameTime().GetFrameDeltaTime();
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
	float DeltaTime = GameTime().GetFrameDeltaTime();
	m_moveSpeed = CVector3::Zero;
	if (PadInput_RT) m_speed = min(MAX_SPEED, m_speed + ACCELERATION);
	if (!PadInput_RT) m_speed = min(max(0.0f, m_speed- ACCELERATION), m_speed + ACCELERATION);
	m_moveSpeed += m_forward * m_speed;

	CQuaternion qRot;
	qRot.SetRotationDeg(m_forward, PadInput_LX * ROLL_SPEED * DeltaTime);
	m_rotation.Multiply(qRot);
	AxisUpdate();
	qRot.SetRotationDeg(m_right, PadInput_LY * PITCH_SPEED * DeltaTime);
	m_rotation.Multiply(qRot);
	AxisUpdate();

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
