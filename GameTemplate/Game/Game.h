#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Title;
class GameStage;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	Title* m_title = nullptr;
	GameStage* m_stage = nullptr;
};

