#include "stdafx.h"
#include "Boss00.h"

#include "ObjMgr.h"
#include "Bullet.h"

CBoss00::CBoss00()
{
}


CBoss00::~CBoss00()
{
	Release();
}

void CBoss00::Initialize()
{
	m_tInfo.vPos = { 300.f, 120.f, 0.f };
	m_tInfo.vSize = { 150.f, 150.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_vOriginPosin = { 0.f, (0.f + m_tInfo.vSize.y / 2 + 20.f), 0.f };

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
}

int CBoss00::Update()
{
	Move();

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	D3DXVec3TransformCoord(&m_vPosin, &m_vOriginPosin, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CBoss00::Late_Update()
{
}

void CBoss00::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	HPEN Brush, oldBrush;

	for (int i = 1; i < 4; ++i)
	{
		switch (i)
		{
		case 1:
			Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldBrush = (HPEN)SelectObject(hDC, Brush);

			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

			SelectObject(hDC, oldBrush);
			DeleteObject(Brush);
			break;
		case 2:
			Brush = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			oldBrush = (HPEN)SelectObject(hDC, Brush);

			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

			SelectObject(hDC, oldBrush);
			DeleteObject(Brush);
			break;
		case 3:
			Brush = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
			oldBrush = (HPEN)SelectObject(hDC, Brush);

			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

			SelectObject(hDC, oldBrush);
			DeleteObject(Brush);
			break;
		}
	}

	Brush = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
	oldBrush = (HPEN)SelectObject(hDC, Brush);

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	SelectObject(hDC, oldBrush);
	DeleteObject(Brush);

	MoveToEx(hDC, int(m_tInfo.vPos.x), int(m_tInfo.vPos.y), nullptr);
	//LineTo(hDC, int(m_vOriginPosin.x), int(m_vOriginPosin.y));
	LineTo(hDC, int(m_vPosin.x), int(m_vPosin.y));
}

void CBoss00::Release()
{
}

void CBoss00::Move()
{
	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		Attack();
		return;
	}
}

void CBoss00::Attack()
{

}
