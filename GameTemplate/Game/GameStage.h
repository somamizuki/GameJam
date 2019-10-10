#pragma once
#include "tkEngine/light/tkDirectionLight.h"

class Player;
class GameCamera;
class Enemy;
class HPbar;
class GameStage:public IGameObject
{
public:
	GameStage();
	~GameStage();

	bool Start();
	void Update();
private:
	Player* m_player = nullptr;
	GameCamera* m_camera = nullptr;
	prefab::CSkinModelRender* m_testStage = nullptr;
	Enemy* m_enemy = nullptr;
	HPbar* m_hpbar = nullptr;
	CLevel m_level;
	prefab::CSky* m_sky = nullptr;
	prefab::CDirectionLight* m_light=nullptr;
	CVector3 m_direction = { 1.0f,-1.0f,0.0f };
	CShaderResourceView m_specSRV;
	bool isGameclear = false;
	bool isGameover = false;
};

