#pragma once

class Player :public IGameObject
{
	
public:
	Player();
	~Player();
	bool Start();
	void Update();
	/*!
	* @brief �|�W�V�������擾
	* @return �|�W�V����
	*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief �O�������擾
	* @return �O����
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	* @brief �E�������擾
	* @return �E����
	*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
	/*!
	* @brief ��������擾
	* @return �����
	*/
	const CVector3& GetUp() const
	{
		return m_up;
	}

	void AddDamage(float damage)
	{
		m_hp -= damage;
	}

private:
	void Execute();
	void Movement();
	void AxisUpdate();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = {0.0f,500.0f,0.0f};
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;

	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::Up;
	float m_speed = 0.0f;
	CVector3 m_moveSpeed = CVector3::Zero;

	float m_hp = 50.0f;
};

