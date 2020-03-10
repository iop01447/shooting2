#include "stdafx.h"
#include "Boss00.h"

#include "ObjMgr.h"
#include "Boss00Bullet1.h"

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
	m_vOriginPosin[0] = { 0.f, (0.f + m_tInfo.vSize.y / 2 + 20.f), 0.f };
	memcpy(&m_vStart, &m_tInfo.vPos, sizeof(m_vStart));

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
	m_dwAttDelay = 800;
	m_dwAttTime = 3000;
	m_dwLastAttTime = GetTickCount();

	m_eState = IDLE;
}

int CBoss00::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformCoord(&m_vPosin[i], &m_vOriginPosin[i], &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CBoss00::Late_Update()
{
}

void CBoss00::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	MoveToEx(hDC, int(m_tInfo.vPos.x), int(m_tInfo.vPos.y), nullptr);
	//LineTo(hDC, int(m_vOriginPosin.x), int(m_vOriginPosin.y));
	LineTo(hDC, int(m_vPosin[0].x), int(m_vPosin[0].y));
}

void CBoss00::Release()
{
}

void CBoss00::Move()
{
	if (360 == m_fAngle)
		m_fAngle = 0.f;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		m_eState = ATTACK;
		Attack();
		return;
	}

	if (0 != m_fAngle)
	{
		if (180 > m_fAngle)
			m_fAngle -= 3.f;
		else
			m_fAngle += 3.f;
	}

	if (START == m_eState)
	{
		BackStartPos();
		return;
	}
}

void CBoss00::Attack()
{
	Attack1();
}

void CBoss00::Attack1()
{
	if (ATTACK != m_eState && ATTACK1 != m_eState)
		return;

	m_fAngle += 3.f;

	D3DXVECTOR3 vDir = m_vPosin[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ㅠ

	if (m_tInfo.vPos.y < m_vPosin[0].y)
		fAngle *= -1.f;

	if (0 == GetTickCount() % 2)
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, Create_Bullet<CBoss00Bullet1>(m_vPosin[0].x, m_vPosin[0].y, fAngle));

	if (m_dwLastAttTime + m_dwAttTime < GetTickCount() || 360 == m_fAngle)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = START;
	}
}

void CBoss00::Attack2()
{
}

void CBoss00::Attack3()
{
}

void CBoss00::BackStartPos()
{
	m_tInfo.vDir = m_vStart - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < m_vStart.y)
		fAngle *= -1.f;

	if (0 > fAngle || 180 < fAngle)
	{
		m_eState = IDLE;
		return;
	}

	m_tInfo.vPos.x += cosf(fAngle);
	m_tInfo.vPos.y -= sinf(fAngle);

	m_dwLastAttTime = GetTickCount();
}
