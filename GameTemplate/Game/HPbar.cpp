#include "stdafx.h"
#include "HPbar.h"
#include "Player.h"

HPbar::HPbar()
{

}
HPbar::~HPbar()
{
	DeleteGO(m_sprite);
	DeleteGO(m_backsprite);
}

bool HPbar::Start()
{
	BarBack();
	MainBar();
	return true;
}

void HPbar::Update()
{
}

void HPbar::MainBar()
{
	//HPバーを生成
	m_sprite = NewGO < prefab::CSpriteRender>(0);
	m_sprite->Init(
		L"sprite/ui_HpBar.dds",
		645.0f,
		7.0f,
		false
	);
	m_scale = { 1.0f,1.0f,0.0f };			//大きさ
	m_sprite->SetPivot({ 0.0f,1.0f });		//ピポット
	m_position = { -628.6f,344.8f,0.0f };	//表示位置
	m_sprite->SetPosition(m_position);		//位置を伝える
	m_sprite->SetScale(m_scale);			//大きさを伝える

	//ReduceHpBar();
}

void HPbar::BarBack()
{
	//HPバーの背景の生成
	m_backsprite = NewGO<prefab::CSpriteRender>(0);
	m_backsprite->Init(
		L"sprite/Ui_BackGround.dds",
		695.0f,
		45.0f,
		false
	);
	m_backsprite->SetPivot({ 0.0f,1.0f });		//ピポット
	m_backPos = { -640.0f,360.0f,0.0f };	//表示位置
	m_backsprite->SetPosition(m_backPos);		//位置を伝える
}

void HPbar::ReduceHpBar()
{	

	//プレイヤーのHPとHPバーを同期させる
	if (m_player != nullptr) {
			m_scale -= {0.1f, 0.0f, 0.0f};
			m_sprite->SetScale(m_scale);
	}
}
