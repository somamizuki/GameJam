#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Player;
class GameCamera;
class Title;
class Enemy;
class HPbar;
class PlayerMissile;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	Player* m_player = nullptr;
	GameCamera* m_camera = nullptr;
	prefab::CSkinModelRender* m_testStage = nullptr;
	Title* m_title = nullptr;
	Enemy* m_enemy = nullptr;
	HPbar* m_hpbar = nullptr;
	PlayerMissile* m_playerMissile = nullptr;
};

