#include "stdafx.h"
#include "FlowerSubBullet.h"


CFlowerSubBullet::CFlowerSubBullet()
{
}


CFlowerSubBullet::~CFlowerSubBullet()
{
}

int CFlowerSubBullet::Update()
{
	if (m_bParentErase)
		return OBJ_DEAD;

	m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlowerSubBullet::Late_Update()
{
	if (m_bUnDead) return;
	if (0 > m_tRect.top || 0 > m_tRect.left
		|| WINCX < m_tRect.right || WINCY < m_tRect.bottom)
		m_bDead = true;
}
