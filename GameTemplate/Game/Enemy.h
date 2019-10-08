#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();

	prefab::CSkinModelRender* skinModelRender = nullptr;		//スキンモデルレンダーの定義
	CVector3 m_position = CVector3::Zero;						//ポジションの定義
	CVector3 m_moveSpeed = CVector3::Zero;						//移動速度の定義
	CCharacterController m_charaCon;							//キャラコン
	
};

