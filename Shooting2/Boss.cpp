#include "stdafx.h"
#include "Boss.h"
#include "Effect.h"
#include "ObjMgr.h"

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Die_Effect()
{
	float fX = (float)(rand() % (int)(m_tInfo.vSize.x) - (m_tInfo.vSize.x / 2) + m_tInfo.vPos.x);
	float fY = (float)(rand() % (int)(m_tInfo.vSize.y) - (m_tInfo.vSize.y / 2) + m_tInfo.vPos.y);

	D3DXVECTOR3 vPos = { fX, fY, 0.f };

	D3DXVECTOR3 vDir = vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	for (int i = 0; i < 3; ++i)
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, Create_Bullet<CEffect>(vPos, vDir));
}
