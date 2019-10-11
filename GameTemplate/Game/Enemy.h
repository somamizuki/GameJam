#pragma once

class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void EnemyUi();
	void OnDestroy();

	//�|�W�V�����̎擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�O�����̎擾

	const CVector3& GetForward() const
	{
		return m_forward;
	}

	//�E�����̎擾

	const CVector3& GetRight() const
	{
		return m_right;
	}

	//������̎擾

	const CVector3& GetUp() const
	{
		return m_up;
	}

	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}

private:

	void GetPlayerInfo();		//�v���C���[�̏����擾
	void EnemyMovement();		//�G�̗������
	void FollowPlayer();		//�v���C���[�ɒǏ]�����鏈��
	void AxisUpdate();
	float AcosWrapper(float dotresult)
	{
		float angle = min(1.0f, max(-1.0f, dotresult));
		angle = acosf(angle);
		return angle;
	}
	
	//�v���C���[���
	struct SPlayerInfo {
		CVector3 Position = CVector3::Zero;
		CVector3 Forward = CVector3::Zero;
		CVector3 Right = CVector3::Zero;
		CVector3 Up = CVector3::Zero;
	};

	prefab::CSpriteRender* m_spriteRender = nullptr;			//�X�v���C�g�����_�[�̒�`
	CVector3 m_UiScale = CVector3::One;							//�X�v���C�g�̑傫��
	CVector3 m_UiPosition = CVector3::Zero;						//�X�v���C�g�̏ꏊ

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_�[�̒�`
	CVector3 m_position = { 0.0f,1000.0f,0.0f };				//�|�W�V�����̒�`
	CQuaternion m_rotation = CQuaternion::Identity;				//�N�H�[�^�j�I���̒�`
	CVector3 m_scale = CVector3::One;							//�傫���̒�`

	//�x�N�g���̕����̒�`
	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::Up;

	//�ړ����x�̒�`
	float m_speed = 0.0f;
	CVector3 m_moveSpeed = CVector3::Zero;
	Player* m_player = nullptr;
	SPlayerInfo m_playerInfo;
	const float MAX_SPEED = 20000.0f;
};

