#include "stdafx.h"
#include "Boss00Bullet1.h"


CBoss00Bullet1::CBoss00Bullet1()
{
}


CBoss00Bullet1::~CBoss00Bullet1()
{
	Release();
}

void CBoss00Bullet1::Initialize()
{
	m_tInfo.vSize.x = 20.f;
	m_tInfo.vSize.y = 20.f;
	m_fSpeed = 5.f;

	Update_Rect();
}

int CBoss00Bullet1::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss00Bullet1::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CBoss00Bullet1::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBoss00Bullet1::Release()
{
}
