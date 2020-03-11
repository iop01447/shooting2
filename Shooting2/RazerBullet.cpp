#include "stdafx.h"
#include "RazerBullet.h"


CRazerBullet::CRazerBullet()
{
}


CRazerBullet::~CRazerBullet()
{
	Release();
}

void CRazerBullet::Initialize()
{
	m_tInfo.vSize.x = 20.f;
	m_tInfo.vSize.y = 20.f;
	m_fSpeed = 5.f;

	Update_Rect();
}

int CRazerBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos +=  m_tInfo.vDir;
	



	Update_Rect();

	return OBJ_NOEVENT;
}

void CRazerBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CRazerBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRazerBullet::Release()
{
}
