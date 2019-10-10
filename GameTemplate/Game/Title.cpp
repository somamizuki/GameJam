#include "stdafx.h"
#include "Title.h"

bool Title::Start()
{
	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->Init(L"sprite/TestTitle2.dds" ,1280.0f, 720.0f);

	m_pressA = NewGO <prefab::CSpriteRender>(0);
	m_pressA->Init(L"sprite/ui_PressA.dds",1280.0f,720.0f);

	m_scale = { 0.7f,0.7f,0.0f };
	m_pressA->SetScale(m_scale);
	m_position = { 0.0f,-120.0f,0.0f };
	m_pressA->SetPosition(m_position);
	return true;
}

void Title::Update()
{
	if (Pad(0).IsTrigger(enButtonA))m_isGameStart = true;
	CVector4 AddColor = CVector4::White;
	if (m_isGameStart)m_mulColor = m_mulColor-AddColor * 1.0f * GameTime().GetFrameDeltaTime();
	m_mulColor.w = 1.0f;
	m_sprite->SetMulColor(m_mulColor);
	m_pressA->SetMulColor(m_mulColor);
	if (m_mulColor.x < 0.1f)DeleteGO(this);
	
	int a = GraphicsEngine().GetFrameBufferWidth();
	int b = 0;


}

void Title::OnDestroy()
{
	DeleteGO(m_sprite);
	DeleteGO(m_pressA);
}