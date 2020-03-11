#include "stdafx.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "AbstractFactory.h"


CBullet::CBullet()
{
	m_eGroup = GROUPID::BULLET;
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.vSize = { 15.f, 15.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;

	Update_Rect();
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//m_tInfo.vPos.y -= m_fSpeed;
	m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (bUnDead) return;
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::Die_Effect()
{
	float fX = (float)(rand() % (int)(m_tInfo.vSize.x) - (m_tInfo.vSize.x / 2) + m_tInfo.vPos.x);
	float fY = (float)(rand() % (int)(m_tInfo.vSize.y) - (m_tInfo.vSize.y / 2) + m_tInfo.vPos.y);

	D3DXVECTOR3 vPos = { fX, fY, 0.f };

	D3DXVECTOR3 vDir = vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	for (int i = 0; i < 3; ++i)
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, CAbstractFactory<CEffect>::Create(vPos, vDir));
}
