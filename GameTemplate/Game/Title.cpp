#include "stdafx.h"
#include "Title.h"

bool Title::Start()
{
	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->Init(L"sprite/TestTitle.dds", GraphicsEngine().GetFrameBufferWidth(), GraphicsEngine().GetFrameBufferHeight());
	return true;
}

void Title::Update()
{
	if (Pad(0).IsTrigger(enButtonA))m_isGameStart = true;
	CVector4 AddColor = CVector4::White;
	if (m_isGameStart)m_mulColor = m_mulColor-AddColor * 0.5f * GameTime().GetFrameDeltaTime();
	m_mulColor.w = 1.0f;
	m_sprite->SetMulColor(m_mulColor);
	if (m_mulColor.x < 0.1f)DeleteGO(this);
}

void Title::OnDestroy()
{
	DeleteGO(m_sprite);
}
