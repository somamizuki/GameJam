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
	m_direction.Normalize();
	
	GraphicsEngine().GetDirectionShadowMap().SetLightDirection(m_direction);
	GraphicsEngine().GetPostEffect().GetDof().Disable();
	GraphicsEngine().GetDirectionShadowMap().SetLightHeight(/*m_player->GetPosition().y+*/5000.0f);


	m_camera = NewGO<GameCamera>(1, "camera");
	m_light = NewGO<prefab::CDirectionLight>(0);
	CVector4 color = CVector4::White*10.0f;
	color.w = 1.0f;
	m_light->SetColor(color);
	m_light->SetDirection(m_direction);
	
	//m_hpbar = NewGO<HPbar>(0, "Hpbar");
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
			Enemy* m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objectdata.position);
			m_enemy->SetRotation(objectdata.rotation);
			m_enemyArray.push_back(m_enemy);
		}
		else if (std::wcscmp(objectdata.name, L"ocean") == 0)
		{
			m_testStage = NewGO<prefab::CSkinModelRender>(0);
			m_testStage->Init(L"modelData/ocean.cmo");
			m_testStage->SetPosition(objectdata.position);
			m_specSRV.CreateFromDDSTextureFromFile(L"modelData/spec.dds");
			m_testStage->FindMaterial([&](auto material) {
				material->SetSpecularMap(m_specSRV.GetBody());
			});
			m_testStage->SetShadowReceiverFlag(true);
			m_rigidBody.CreateMesh(objectdata.position, objectdata.rotation, m_testStage->GetSkinModelData());
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
	int i = 0;
	for (const auto& enemy : m_enemyArray)
	{
		if (enemy->IsDead())i++;
	}
	if (i == m_enemyArray.size())
	{
		m_isGameClear = true;
	}
	if (m_isGameClear&& !m_flag) {
		m_sprite = NewGO<prefab::CSpriteRender>(0);
		m_sprite->Init(L"sprite/GameClear.dds",1280.0f,720.0f);
		m_flag = true;
	}/*else if(m_isGameOver && m_sprite == nullptr) {
		m_sprite = NewGO<prefab::CSpriteRender>(0);
		m_sprite->Init(L"sprite/GameOver.dds", 1280.0f, 720.0f);
	}*/
	if (m_sprite != nullptr && Pad(0).IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void GameStage::OnDestroy()
{
	DeleteGO(m_camera);
	DeleteGO(m_light);
	//DeleteGO(m_hpbar);
	DeleteGO(m_sky);
	DeleteGO(m_player);
	DeleteGO(m_sprite);
	DeleteGO(m_testStage);
}
