#include "stdafx.h"
#include "Boss02Bullet.h"


CBoss02Bullet::CBoss02Bullet()
{
}


CBoss02Bullet::~CBoss02Bullet()
{
	Release();
}

void CBoss02Bullet::Initialize()
{
	m_tInfo.vSize.x = 10.f;
	m_tInfo.vSize.y = 10.f;
	m_fSpeed = 5.f;

	Update_Rect();
}

int CBoss02Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;

	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss02Bullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CBoss02Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBoss02Bullet::Release()
{
}
