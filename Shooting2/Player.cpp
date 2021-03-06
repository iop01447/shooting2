#include "stdafx.h"
#include "Player.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"
#include "PlayerBullet.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 300.f, (float)(WINCY + 100), 0.f };
	m_tInfo.vSize = { 10.f, 10.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f }; 
	m_vPosin = { m_tInfo.vPos.x, (m_tInfo.vPos.y - m_tInfo.vSize.y / 2) - 15.f, 0.f };

	m_vStart = { 300.f, 700.f, 0.f };

	m_vOrigin[0] = { -3.f, 2.f, 0.f };
	m_vOrigin[1] = { 0.f, -1.f, 0.f };
	m_vOrigin[2] = { 3.f, 2.f, 0.f };
	m_vOrigin[3] = { 0.f, 1.f, 0.f };
	for (int i = 0; i < 4; ++i) {
		m_vOrigin[i].x *= m_tInfo.vSize.x;
		m_vOrigin[i].y *= m_tInfo.vSize.y;
	}

	m_fAngle = 0.f; 
	m_fSpeed = 5.f; 

	m_dwAttDelay = 200;
	m_dwLastAttTime = GetTickCount();

	m_bEvasive = false;			// 회피중인지 체크용
	m_fEvaAngle = 0.f;			// 회피 회전
	m_bStart = true;
	m_bEnd = false;
}

int CPlayer::Update()
{
	if (m_bStart)
	{
		m_fAngle = 0.f;
		m_tInfo.vPos.y += m_tInfo.vDir.y * (m_fSpeed / 2);

		if (m_tInfo.vPos.y < m_vStart.y)
			m_bStart = false;

		D3DXMATRIX matScale, matRotZ, matTrance;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrance;

		m_vPosin = { m_tInfo.vPos.x, (m_tInfo.vPos.y - m_tInfo.vSize.y / 2) - 15.f, 0.f };

		for (int i = 0; i < 4; ++i)
			D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

		return OBJ_NOEVENT;
	}

	if (m_bEnd)
	{
		m_fAngle = 0.f;
		m_tInfo.vPos.y += m_tInfo.vDir.y * (m_fSpeed / 2);

		if (m_tInfo.vPos.y < -100)
		{
			m_bEnd = false;
			m_tInfo.vPos = { 300.f, (float)(WINCY + 100), 0.f };
			m_bStart = true;
		}
		D3DXMATRIX matScale, matRotZ, matTrance;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrance;

		m_vPosin = { m_tInfo.vPos.x, (m_tInfo.vPos.y - m_tInfo.vSize.y / 2) - 15.f, 0.f };

		for (int i = 0; i < 4; ++i)
			D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

		return OBJ_NOEVENT;
	}

	KeyCheck(); 
	Boundary_Check();

	D3DXMATRIX matScale, matRotZ, matTrance; 
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	if (m_bEvasive)
	{
		m_fEvaAngle += 5.f;
		D3DXMatrixRotationY(&matRotZ, D3DXToRadian(m_fEvaAngle));
		if (180 <= m_fEvaAngle)
		{
			m_fEvaAngle = 0;
			m_bEvasive = false;
		}
	}
	else
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f); 
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	m_vPosin = { m_tInfo.vPos.x, (m_tInfo.vPos.y - m_tInfo.vSize.y / 2) - 15.f, 0.f };

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1 ; i < 4 ; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

#ifdef _DEBUG
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
#endif
}

void CPlayer::Release()
{
}

void CPlayer::KeyCheck()
{
	m_fAngle = 0.f;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos.y -= m_fSpeed;
		m_fAngle = 0.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos.x -= m_fSpeed;
		m_fAngle = -15.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos.x += m_fSpeed;
		m_fAngle = 15.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos.y += m_fSpeed;
		m_fAngle = 0.f;
	}

	if (!m_bEvasive && CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, Create_Bullet<CPlayerBullet>(m_vPosin.x, m_vPosin.y));
			m_dwLastAttTime = GetTickCount();
		}
	}

	if (!m_bEvasive && CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
	{
		m_bEvasive = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		DestroyWindow(g_hWnd);
	}
}

void CPlayer::Boundary_Check()
{
}

