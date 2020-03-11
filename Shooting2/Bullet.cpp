#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
	m_eGroup = GROUPID::BULLET;
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.vSize = { 15.f, 15.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;

	Update_Rect();
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//m_tInfo.vPos.y -= m_fSpeed;
	m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
