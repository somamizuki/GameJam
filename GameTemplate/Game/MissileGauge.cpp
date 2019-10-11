#include "stdafx.h"
#include "MissileGauge.h"
#include "PlayerMissile.h"

MissileGauge::MissileGauge()
{
}

MissileGauge::~MissileGauge()
{
}

bool MissileGauge::Start()
{
	//ミサイルゲージの背景。
	m_back = NewGO<prefab::CSpriteRender>(0);
	m_back->Init(
		L"sprite/Ui_MissileBack.dds",
		450.0f,
		45.0f,
		false
	);
	m_back->SetPivot({ 1.0f, 0.0f });
	m_backPos = { 643.2f,-360.0f,0.0f };
	m_back->SetPosition(m_backPos);

	//ミサイルゲージ。
	m_gauge = NewGO<prefab::CSpriteRender>(0);
	m_gauge->Init(
		L"sprite/Ui_MissileBark.dds",
		450.0f,
		45.0f,
		false
	);
	m_scale = { 1.0f,1.0f,0.0f };
	m_gauge->SetPivot({ 1.0f, 0.0f });
	m_gaugePos = { 643.2f,-360.0f,0.0f };
	m_gauge->SetPosition(m_gaugePos);
	m_gauge->SetScale(m_scale);


	return true;
}

void MissileGauge::Update()
{
}

void MissileGauge::OnDestroy()
{
	DeleteGO(m_back);
	DeleteGO(m_gauge);
}
