#pragma once

class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void SetPosition(const CVector3& position)
	{
		MainCamera().SetPosition(position);
	}

	void SetTarget(const CVector3& target)
	{
		MainCamera().SetTarget(target);
	}

	void SetUp(const CVector3& up)
	{
		MainCamera().SetUp(up);
	}

	void SetNear(float fnear)
	{
		MainCamera().SetNear(fnear);
	}

	void SetFar(float ffar)
	{
		MainCamera().SetFar(ffar);
	}

	const CVector3& GetPosition() const
	{
		return MainCamera().GetPosition();
	}

	void CameraUpdate()
	{
		MainCamera().Update();
	}
private:
	void Movement();
	Player* m_player = nullptr;
	const float MAX_DIST = 2000.0f;
};

