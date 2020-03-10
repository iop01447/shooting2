#include "stdafx.h"
#include "Player.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 300.f, 700.f, 0.f };
	m_tInfo.vSize = { 10.f, 10.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f }; 
	m_vPosin = { m_tInfo.vPos.x, (m_tInfo.vPos.y - m_tInfo.vSize.y / 2), 0.f };

	m_vOrigin[0] = { -3.f, 2.f, 0.f };
	m_vOrigin[1] = { 0.f, -1.f, 0.f };
	m_vOrigin[2] = { 3.f, 2.f, 0.f };
	m_vOrigin[3] = { 0.f,1.f, 0.f };
	for (int i = 0; i < 4; ++i) {
		m_vOrigin[i].x *= m_tInfo.vSize.x;
		m_vOrigin[i].y *= m_tInfo.vSize.y;
	}

	m_fAngle = 0.f; 
	m_fSpeed = 5.f; 

}

int CPlayer::Update()
{
	KeyCheck(); 
	Boundary_Check();

	D3DXMATRIX matScale, matRotZ, matTrance; 
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f); 
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

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

}

void CPlayer::Release()
{
}

void CPlayer::KeyCheck()
{
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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, Create_Bullet<CBullet>(m_vPosin.x, m_vPosin.y));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		DestroyWindow(g_hWnd);
	}
}

void CPlayer::Boundary_Check()
{
}

