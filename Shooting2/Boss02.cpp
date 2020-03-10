#include "stdafx.h"
#include "Boss02.h"


CBoss02::CBoss02()
{
}


CBoss02::~CBoss02()
{
}

void CBoss02::Initialize()
{
	m_tInfo.vPos = { 300.f, 100.f, 0.f };
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//윗점
	m_vOrigin[0] = { -m_tInfo.vSize.x,-m_tInfo.vSize.y * 0.5f, 0.f };
	//우하단
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	//좌하단
	m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_vOrigin[3] = {};
	m_vOrigin[4] = {};
	m_vOrigin[5] = {};


	m_fAngle = 0.f;
	m_fSpeed = 5.f;

	m_tStatus.iHp = 1000;
}

int CBoss02::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (600 <= m_tStatus.iHp)
	{
		//중앙상단
		m_vOrigin[0] = { -m_tInfo.vSize.x,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
	}
	// 사각
	else if (400 <= m_tStatus.iHp)
	{
		//좌상단
		m_vOrigin[0] = { -m_tInfo.vSize.x,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우상단
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[2] = { +m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
	}
	// 오각
	else if (200 <= m_tStatus.iHp)
	{
		//중앙상단
		m_vOrigin[0] = { -m_tInfo.vSize.x,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우중단
		m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[3] = {};
		//좌중단
		m_vOrigin[4] = {};
	}

	// 육각
	else if (0 <= m_tStatus.iHp)
	{
		m_vOrigin[0] = { -m_tInfo.vSize.x,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		m_vOrigin[4] = {};
		m_vOrigin[5] = {};
	}
	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CBoss02::Late_Update()
{
	Update_Rect();
}

void CBoss02::Render(HDC hDC)
{
	// 원
	if (800 <= m_tStatus.iHp)
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	// 삼각
	else if (600 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 3; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}
	// 사각
	else if (400 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 4; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}
	// 오각
	else if (200 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 5; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}

	// 육각
	else if (0 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 6; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}
	//MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	//HPEN Brush, oldBrush;

	//for (int i = 1; i < 4; ++i)
	//{
	//	switch (i)
	//	{
	//	case 1:
	//		Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//		oldBrush = (HPEN)SelectObject(hDC, Brush);

	//		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	//		SelectObject(hDC, oldBrush);
	//		DeleteObject(Brush);
	//		break;
	//	case 2:
	//		Brush = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	//		oldBrush = (HPEN)SelectObject(hDC, Brush);

	//		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	//		SelectObject(hDC, oldBrush);
	//		DeleteObject(Brush);
	//		break;
	//	case 3:
	//		Brush = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//		oldBrush = (HPEN)SelectObject(hDC, Brush);

	//		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	//		SelectObject(hDC, oldBrush);
	//		DeleteObject(Brush);
	//		break;
	//	}
	//}

	//Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
	//oldBrush = (HPEN)SelectObject(hDC, Brush);

	//LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	//SelectObject(hDC, oldBrush);
	//DeleteObject(Brush);
}

void CBoss02::Release()
{
}

void CBoss02::Move()
{
}

void CBoss02::Attack()
{
}
