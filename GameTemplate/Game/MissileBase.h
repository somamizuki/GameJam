#pragma once
class MissileBase : public IGameObject
{
public:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale;
	CQuaternion m_rotation;
	prefab::CEffect* m_effect;
};

