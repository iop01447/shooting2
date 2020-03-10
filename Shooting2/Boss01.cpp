#include "stdafx.h"
#include "Boss01.h"


CBoss01::CBoss01()
{
}

CBoss01::~CBoss01()
{
	Release();
}

void CBoss01::Initialize()
{
	m_tInfo.vPos = { 300.f, 100.f, 0.f };
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

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

int CBoss01::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss01::Late_Update()
{
}

void CBoss01::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
}

void CBoss01::Release()
{
}

void CBoss01::Move()
{
}

void CBoss01::Attack()
{
}
