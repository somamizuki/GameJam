#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Title.h"
#include "GameStage.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	GraphicsEngine().GetPostEffect().GetDof().Disable();
	m_title = NewGO<Title>(0, "title");


	return true;
}

void Game::Update()
{
	if (m_title != nullptr && m_title->IsDead())m_title = nullptr;
	if (m_title == nullptr)
	{
		if (!m_stage)
		{
			m_stage = NewGO<GameStage>(0, "stage");
		}
		else
		{
			//if(m_stage)
		}
	}

}