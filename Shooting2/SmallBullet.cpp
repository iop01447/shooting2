#include "stdafx.h"
#include "SmallBullet.h"


CSmallBullet::CSmallBullet()
{
}


CSmallBullet::~CSmallBullet()
{
}

void CSmallBullet::Initialize()
{
	m_tInfo.vSize = { 5.f, 5.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };

	m_vCenter = m_tInfo.vPos;

	m_fSpeed = 8.f;
	m_fAngle = 0.f;
	m_fRotDis = 30.f;

	m_iRenderIdx = 2;

	Update_Rect();
}

int CSmallBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_vCenter.x = m_pTarget->Get_Rect().left + 7.f;
	m_vCenter.y += m_fSpeed + 2.5f;

	m_fAngle += m_fSpeed;

	if (m_tInfo.vPos.x < m_vCenter.x + cosf(D3DXToRadian(m_fAngle)) * m_fRotDis)
		m_iRenderIdx = 2;
	else
		m_iRenderIdx = 0;

	m_tInfo.vPos.x = m_vCenter.x + cosf(D3DXToRadian(m_fAngle)) * m_fRotDis;
	m_tInfo.vPos.y = m_vCenter.y - sinf(D3DXToRadian(m_fAngle)) * (m_fRotDis / 2);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CSmallBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CSmallBullet::Render(HDC hDC)
{
	HPEN Brush = nullptr;
	HPEN oldBrush = nullptr;

	Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
	oldBrush = (HPEN)SelectObject(hDC, Brush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(Brush);
}

void CSmallBullet::Release()
{
}
