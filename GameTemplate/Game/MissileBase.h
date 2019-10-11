#pragma once
class MissileBase : public IGameObject
{
public:
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	void Fire(float speed)
	{
		m_isFire = true;
		m_speed = speed;
	}

protected:
	void AxisUpdate()
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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation;
	prefab::CEffect* m_effect;
	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::CVector3::Up;
	CVector3 m_moveSpeed = CVector3::Zero;
	float AcosWrapper(float dotresult)
	{
		float angle = min(max(-1.0f, dotresult), 1.0f);
		angle = acosf(angle);
		return angle;
	}
	bool m_isFire = false;
	float m_speed = 0.0f;
	float m_timer = 0.0f;
	const float MAX_SPEED = 60000.0f;
};

