#pragma once

class PlayerMissile;
class Enemy;
class GameStage;
class MissileGauge;
class Player :public IGameObject
{

public:
	Player();
	~Player();
	bool Start();
	void Update();
	void OnDestroy();
	/*!
	* @brief ポジションを取得
	* @return ポジション
	*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief 前方向を取得
	* @return 前方向
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	* @brief 右方向を取得
	* @return 右方向
	*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
	/*!
	* @brief 上方向を取得
	* @return 上方向
	*/
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

	void AddDamage(float damage)
	{
		m_hp -= damage;
	}

private:
	void Execute();
	void Movement();
	void AxisUpdate();
	void MissileManager();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = { 0.0f,500.0f,0.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;

	prefab::CSpriteRender* m_spriteUiRender = nullptr;
	CVector3 m_UiPosition = CVector3::Zero;
	CVector3 m_UiScale = CVector3::One;

	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_UiTarget = CVector3::Zero;
	CVector3 m_UiTargetScale = CVector3::One;

	MissileGauge* m_missileGauge = nullptr;

	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::Up;
	float m_speed = 0.0f;
	CVector3 m_moveSpeed = CVector3::Zero;
	PlayerMissile* m_missile = nullptr;
	CLevel m_level;
	float m_hp = 50.0f;

	CVector3 m_tomissilePos = CVector3::Zero;

	CShaderResourceView m_normalSRV;
	CShaderResourceView m_specSRV;
	prefab::CEffect* m_effect = nullptr;
	CCharacterController m_characon;
	GameStage* m_stage = nullptr;

	//prefab::CEffect* effect = NewGO <prefab::CEffect>(0);
	CVector3 m_animPos = CVector3::Zero;
	CVector3 m_animScale = CVector3::One;
};

