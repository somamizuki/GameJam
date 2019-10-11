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

	//ポジションの取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//前方向の取得

	const CVector3& GetForward() const
	{
		return m_forward;
	}

	//右方向の取得

	const CVector3& GetRight() const
	{
		return m_right;
	}

	//上方向の取得

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

	void GetPlayerInfo();		//プレイヤーの情報を取得
	void EnemyMovement();		//敵の立ち回り
	void FollowPlayer();		//プレイヤーに追従させる処理
	void AxisUpdate();
	float AcosWrapper(float dotresult)
	{
		float angle = min(1.0f, max(-1.0f, dotresult));
		angle = acosf(angle);
		return angle;
	}
	
	//プレイヤー情報
	struct SPlayerInfo {
		CVector3 Position = CVector3::Zero;
		CVector3 Forward = CVector3::Zero;
		CVector3 Right = CVector3::Zero;
		CVector3 Up = CVector3::Zero;
	};

	prefab::CSpriteRender* m_spriteRender = nullptr;			//スプライトレンダーの定義
	CVector3 m_UiScale = CVector3::One;							//スプライトの大きさ
	CVector3 m_UiPosition = CVector3::Zero;						//スプライトの場所

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダーの定義
	CVector3 m_position = { 0.0f,1000.0f,0.0f };				//ポジションの定義
	CQuaternion m_rotation = CQuaternion::Identity;				//クォータニオンの定義
	CVector3 m_scale = CVector3::One;							//大きさの定義

	//ベクトルの方向の定義
	CVector3 m_forward = CVector3::Front;
	CVector3 m_right = CVector3::Right;
	CVector3 m_up = CVector3::Up;

	//移動速度の定義
	float m_speed = 0.0f;
	CVector3 m_moveSpeed = CVector3::Zero;
	Player* m_player = nullptr;
	SPlayerInfo m_playerInfo;
	const float MAX_SPEED = 20000.0f;
};

