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
	//HP�o�[�𐶐�
	m_sprite = NewGO < prefab::CSpriteRender>(0);
	m_sprite->Init(
		L"sprite/ui_HpBar.dds",
		645.0f,
		7.0f,
		false
	);
	m_scale = { 1.0f,1.0f,0.0f };			//�傫��
	m_sprite->SetPivot({ 0.0f,1.0f });		//�s�|�b�g
	m_position = { -628.6f,344.8f,0.0f };	//�\���ʒu
	m_sprite->SetPosition(m_position);		//�ʒu��`����
	m_sprite->SetScale(m_scale);			//�傫����`����

	//ReduceHpBar();
}

void HPbar::BarBack()
{
	//HP�o�[�̔w�i�̐���
	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->Init(
		L"sprite/Ui_BackGround.dds",
		695.0f,
		45.0f,
		false
	);
	m_sprite->SetPivot({ 0.0f,1.0f });		//�s�|�b�g
	m_position = { -640.0f,360.0f,0.0f };	//�\���ʒu
	m_sprite->SetPosition(m_position);		//�ʒu��`����
}
/*
float HPbar::ReduceHpBar()
{
	//�v���C���[��HP�������������̂��v�Z
	50 - m_hp = m_reduceHp;			//�G���[�o���Ă�^������z��̃v���O���� ��

	//�v���C���[��HP��HP�o�[�𓯊�������
	if (m_player != nullptr) {
		if (m_reduceHp >= 10) {
			m_scale -= {-0.2f, 0.0f, 0.0f};
		}
	}
}
*/