#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player.h"
#include "GameCamera.h"
#include "Title.h"
#include "Enemy.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	GraphicsEngine().GetPostEffect().GetDof().Disable();
	m_testStage = NewGO<prefab::CSkinModelRender>(0);
	m_testStage->Init(L"modelData/TestStage.cmo");
	m_title = NewGO<Title>(0, "title");


	return true;
}

void Game::Update()
{
	if (m_title != nullptr && m_title->IsDead())m_title = nullptr;
	if (m_title == nullptr)
	{
		if(!m_player)m_player = NewGO<Player>(0, "player");
		if(!m_camera)m_camera = NewGO<GameCamera>(1, "camera");
		if (!m_enemy)m_enemy = NewGO<Enemy>(1, "enemy");
	}

}