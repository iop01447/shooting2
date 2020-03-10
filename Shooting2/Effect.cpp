#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
	m_tInfo.vSize.x = 5.f;
	m_tInfo.vSize.y = 5.f;
	m_fSpeed = (float)(rand() % 10) / 10.f + 1.f;

	m_dwDeadTime = 1000;
	m_dwDeltaTime = GetTickCount();

	Update_Rect();
}

int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CEffect::Render(HDC hDC)
{
	if (0 == rand() % 2)
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	else
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CEffect::Release()
{
}
