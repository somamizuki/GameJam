#pragma once
class MissileBase : public IGameObject
{
public:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::One;
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
};

