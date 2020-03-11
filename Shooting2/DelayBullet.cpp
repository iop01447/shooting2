#include "stdafx.h"
#include "DelayBullet.h"
#include "ObjMgr.h"

CDelayBullet::CDelayBullet()
{
}


CDelayBullet::~CDelayBullet()
{
}

void CDelayBullet::Initialize()
{
	m_tInfo.vSize = { 30.f, 30.f, 0.f };
	m_fSpeed = 5.f;

	m_dwDelay = 1000 + rand() % 2000;
	m_dwLastTime = GetTickCount();

	Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));

//	m_tStatus.iHp = 1;

	Update_Rect();
}

int CDelayBullet::Update()
{
	if (m_bDead) {
		for (int i = 0; i < 50; ++i)
			Die_Effect();

		return OBJ_DEAD;
	}

	if (!m_bMove) {
		static int iCnt = 3;
		static int iAdd = 2;
		if (iCnt--) {
			m_tInfo.vPos.x += iAdd;
		}
		else {
			iCnt = 3;
			iAdd *= -1;
		}
	}

	if (!m_bMove && (m_dwDelay + m_dwLastTime < GetTickCount())) {
		m_bMove = true;
		D3DXVec3Normalize(&m_tInfo.vDir, &(m_pTarget->Get_Info().vPos - m_tInfo.vPos));
	}

	if(m_bMove)
		m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CDelayBullet::Late_Update()
{
//	if (m_tStatus.iHp < 1)
	//	m_bDead = true;
}
