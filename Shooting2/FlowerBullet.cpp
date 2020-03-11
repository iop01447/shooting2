#include "stdafx.h"
#include "FlowerBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "FlowerSubBullet.h"


CFlowerBullet::CFlowerBullet()
{
}


CFlowerBullet::~CFlowerBullet()
{
}

void CFlowerBullet::Initialize()
{
	//m_tInfo.vSize = { 5.f, 5.f, 0.f };
	m_tInfo.vSize = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 0.f };

	m_fSpeed = 3.f;
	m_fAngle = 0;

	float fA = 7, fB = 2;
	D3DXVECTOR3 vOrigin = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vPos = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vDir = { 0.f, 0.f, 0.f };
	for (float theta = 0; theta < 2 * 3.14; theta += 0.02f) {
		float fR = sin(fA / fB * theta);

		vPos.x = fR * cos(theta);
		vPos.y = fR * sin(theta);
		vPos *= 70; // scale
		vOrigin = vPos;

		vPos += m_tInfo.vPos;
		CObj* bullet = CAbstractFactory<CFlowerSubBullet>::Create(vPos, vDir);
		bullet->Set_Size(5, 5);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, bullet);
		m_mapBullet.emplace(bullet, vOrigin);
	}

	Update_Rect();
}

int CFlowerBullet::Update()
{
	if (m_bDead) {
		for (auto& bullet : m_mapBullet) {
			if (bullet.first)
				dynamic_cast<CFlowerSubBullet*>(bullet.first)->Set_ParentErase(true);
		}
		return OBJ_DEAD;
	}

	m_fAngle = fmod(m_fAngle + 5, 360.f);
	for (auto& bullet : m_mapBullet) {
		D3DXMATRIX matRotZ;
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

		D3DXVECTOR3 vPos;
		D3DXVec3TransformCoord(&vPos, &bullet.second, &matRotZ);
		vPos += m_tInfo.vPos;
		bullet.first->Set_Pos(vPos.x, vPos.y);
	}

	m_tInfo.vDir.x = sin(D3DXToRadian(m_fAngle)) * 1.5f;
	m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlowerBullet::Late_Update()
{
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;

	for (auto iter = m_mapBullet.begin(); iter != m_mapBullet.end();) {
		if ((iter->first)->Get_Dead()) {
			dynamic_cast<CFlowerSubBullet*>(iter->first)->Set_ParentErase(true);
			iter = m_mapBullet.erase(iter);
		}
		else
			++iter;
	}
}

void CFlowerBullet::Render(HDC hDC)
{
	CBullet::Render(hDC);
}

void CFlowerBullet::Release()
{
}
