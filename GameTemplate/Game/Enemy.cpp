#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	DeleteGO(skinModelRender);		//skinModelRender��������
}

bool Enemy::Start()
{
	skinModelRender = NewGO<prefab::CSkinModelRender>(0);		//�X�L�����f�������_�[
	//skinModelRender->Init(L"");									//�\�����������f���̃p�X

	//skinModelRender->SetShadowCasterFlag(true);					//���f���̉e��`��

	return true;
}

void Enemy::Update()
{

}