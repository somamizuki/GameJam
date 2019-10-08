#pragma once

class Player :public IGameObject
{
	
public:
	Player();
	~Player();
	bool Start();
	void Update();
private:
	void Execute();
	void Movement();
	void AxisUpdate();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;

	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::Up;
};

