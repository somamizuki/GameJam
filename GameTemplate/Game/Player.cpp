#include "stdafx.h"
#include "Player.h"

namespace {
	const float MAX_SPEED = 2000.0f;
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
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void Player::Movement()
{
	float PadInput_LX = Pad(0).GetLStickXF();
	float PadInput_LY = Pad(0).GetLStickYF();


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
