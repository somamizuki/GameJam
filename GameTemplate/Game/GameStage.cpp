#include "stdafx.h"
#include "GameStage.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "HPbar.h"

GameStage::GameStage()
{
}

GameStage::~GameStage()
{
}

bool GameStage::Start()
{
	GraphicsEngine().GetPostEffect().GetDof().Disable();



	m_camera = NewGO<GameCamera>(1, "camera");
	m_light = NewGO<prefab::CDirectionLight>(0);
	CVector4 color = CVector4::White*10.0f;
	color.w = 1.0f;
	m_light->SetColor(color);
	m_hpbar = NewGO<HPbar>(0, "Hpbar");
	m_sky = NewGO<prefab::CSky>(0);
	m_sky->SetScale({ 800000.0f,800000.0f ,800000.0f });
		m_level.Init(L"level/stage_level.tkl", [&](LevelObjectData& objectdata) {
		if (std::wcscmp(objectdata.name, L"StarSparrow") == 0)
		{
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objectdata.position);
			m_player->SetRotation(objectdata.rotation);
		}
		else if (std::wcscmp(objectdata.name, L"Enemy") == 0)
		{
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objectdata.position);
			m_enemy->SetRotation(objectdata.rotation);
		}
		else if (std::wcscmp(objectdata.name, L"ocean") == 0)
		{
			return false;
		}
		else if (std::wcscmp(objectdata.name, L"island") == 0)
		{
			return false;
		}
		else if (std::wcscmp(objectdata.name, L"island_long") == 0)
		{
			return false;
		}
		else if (std::wcscmp(objectdata.name, L"island_mount") == 0)
		{
			return false;
		}
		return true;
	});
	return true;
}

void GameStage::Update()
{

}
