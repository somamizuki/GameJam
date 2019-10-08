#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();

	prefab::CSkinModelRender* skinModelRender = nullptr;		//�X�L�����f�������_�[�̒�`
	CVector3 m_position = CVector3::Zero;						//�|�W�V�����̒�`
	CVector3 m_moveSpeed = CVector3::Zero;						//�ړ����x�̒�`
	CCharacterController m_charaCon;							//�L�����R��
	
};

