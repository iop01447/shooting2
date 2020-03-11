#include "stdafx.h"
#include "RazerBullet.h"
#include "Boss02.h"
#include "ObjMgr.h"
#include "MainGame.h"

CRazerBullet::CRazerBullet()
	:m_pBoss2(nullptr)
{
}


CRazerBullet::~CRazerBullet()
{
	Release();
}

void CRazerBullet::Initialize()
{
	m_tInfo.vSize.x = 20.f;
	m_tInfo.vSize.y = 20.f;
	m_fSpeed = 5.f;
	
	m_pBoss2 = CObjMgr::Get_Instance()->Get_Obj(OBJID::BOSS);

	

	Update_Rect();
}

int CRazerBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_pBoss2==nullptr)
		return OBJ_DEAD;

		m_vOrigin.x = (m_tInfo.vPos.x - m_pBoss2->Get_Info().vPos.x)/10;

	
		m_vOrigin.y = (m_tInfo.vPos.y - m_pBoss2->Get_Info().vPos.y)/10;
	D3DXMATRIX matRotZ, matTrance;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(1));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matRotZ*matTrance;


	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_vOrigin, &m_tInfo.matWorld);

	Update_Rect();

	return OBJ_NOEVENT;

}

void CRazerBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}

void CRazerBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRazerBullet::Release()
{
}
