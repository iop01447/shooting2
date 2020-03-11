#include "stdafx.h"
#include "Boss00Bullet2.h"


CBoss00Bullet2::CBoss00Bullet2()
{
}


CBoss00Bullet2::~CBoss00Bullet2()
{
	Release();
}

void CBoss00Bullet2::Initialize()
{
	m_tInfo.vSize = { 10.f, 30.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f + 2.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f - 2.5f, -m_tInfo.vSize.y * 0.5f, 0.f };

	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.25f, 0.f };
	m_vOrigin[3] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.25f, 0.f };

	//원점 기준 우 하단. 
	m_vOrigin[4] = { m_tInfo.vSize.x * 0.5f - 2.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[5] = { -m_tInfo.vSize.x * 0.5f + 2.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_vOrigin[6] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.25f, 0.f };
	m_vOrigin[7] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.25f, 0.f };

	m_fSpeed = 7.f;
	m_fAngle = 0.f;

	m_iRand = rand() % 2;

	Update_Rect();
}

int CBoss00Bullet2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (0 == m_iRand)
		m_fAngle += 10.f;
	else
		m_fAngle -= 10.f;

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss00Bullet2::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CBoss00Bullet2::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[7].x), int(m_vPoint[7].y), nullptr);

	for (int i = 0; i < 8; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
}

void CBoss00Bullet2::Release()
{
}
