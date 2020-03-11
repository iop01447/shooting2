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
	float r = rand() % 5 + 3.f;
	m_tInfo.vSize = { r, r, 0.f };
	m_fSpeed = (float)(rand() % 10) / 10.f + 1.3f;

	m_dwDeadTime = 1500;
	m_dwDeltaTime = GetTickCount();

	m_iRand = rand() % 2;
	m_iColor = rand() % 4;

	Update_Rect();
}

int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	//m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
	//m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;

	if (m_dwDeltaTime + m_dwDeadTime < GetTickCount())
		m_bDead = true;
}

void CEffect::Render(HDC hDC)
{
	HPEN Brush = nullptr;
	HPEN oldBrush = nullptr;

	switch (m_iColor)
	{
	case 0:
		Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		oldBrush = (HPEN)SelectObject(hDC, Brush);
		break;
	case 1:
		Brush = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		oldBrush = (HPEN)SelectObject(hDC, Brush);
		break;
	case 2:
		Brush = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		oldBrush = (HPEN)SelectObject(hDC, Brush);
		break;
	case 3:
		Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
		oldBrush = (HPEN)SelectObject(hDC, Brush);
		break;
	default:
		break;
	}

	if (0 == m_iRand)
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	else
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(Brush);
}

void CEffect::Release()
{
}
