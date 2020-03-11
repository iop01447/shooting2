#include "stdafx.h"
#include "RotBullet.h"


CRotBullet::CRotBullet()
{
}


CRotBullet::~CRotBullet()
{
	Release();
}

void CRotBullet::Initialize()
{
	m_tInfo.vSize.x = 10.f;
	m_tInfo.vSize.y = 10.f;
	m_fSpeed = 5.f;

	m_fRotAngle = 0.f;
	m_fRotSpeed = 90.f;
	m_fRotDis = 10.f;
	m_bDir = true;
	Update_Rect();

	m_tCenter= m_tInfo.vPos;
}

int CRotBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	//m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	m_tCenter.x += m_tInfo.vDir.x * m_fSpeed;
	m_tCenter.y += m_tInfo.vDir.y * m_fSpeed;
	

	m_fRotAngle += m_fRotSpeed;

	if (m_bDir)
	{
		m_tInfo.vPos.x = m_tCenter.x + cosf(m_fRotAngle * PI / 180.f) * m_fRotDis;
		m_tInfo.vPos.y = m_tCenter.y - sinf(m_fRotAngle * PI / 180.f) * m_fRotDis;
		m_bDir = !m_bDir;
	}
	else
	{
		m_tInfo.vPos.x = m_tCenter.x - sinf (m_fRotAngle * PI / 180.f) * m_fRotDis;
		m_tInfo.vPos.y = m_tCenter.y + cosf(m_fRotAngle * PI / 180.f) * m_fRotDis;
		m_bDir = !m_bDir;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRotBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CRotBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRotBullet::Release()
{
}
