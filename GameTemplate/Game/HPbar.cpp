#include "stdafx.h"
#include "HPbar.h"
#include "Player.h"

HPbar::HPbar()
{

}
HPbar::~HPbar()
{

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
	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->Init(
		L"sprite/Ui_BackGround.dds",
		695.0f,
		45.0f,
		false
	);
	m_sprite->SetPivot({ 0.0f,1.0f });		//ピポット
	m_position = { -640.0f,360.0f,0.0f };	//表示位置
	m_sprite->SetPosition(m_position);		//位置を伝える
}
/*
float HPbar::ReduceHpBar()
{
	//プレイヤーのHPがいくつ減ったのか計算
	50 - m_hp = m_reduceHp;			//エラー出してる型がある想定のプログラム 仮

	//プレイヤーのHPとHPバーを同期させる
	if (m_player != nullptr) {
		if (m_reduceHp >= 10) {
			m_scale -= {-0.2f, 0.0f, 0.0f};
		}
	}
}
*/