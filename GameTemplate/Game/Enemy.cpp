#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	DeleteGO(skinModelRender);		//skinModelRenderを初期化
}

bool Enemy::Start()
{
	skinModelRender = NewGO<prefab::CSkinModelRender>(0);		//スキンモデルレンダー
	//skinModelRender->Init(L"");									//表示したいモデルのパス

	//skinModelRender->SetShadowCasterFlag(true);					//モデルの影を描画

	return true;
}

void Enemy::Update()
{

}