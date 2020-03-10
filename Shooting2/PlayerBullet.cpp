#include "stdafx.h"
#include "PlayerBullet.h"


CPlayerBullet::CPlayerBullet()
{
}


CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
	m_tInfo.vSize = { 10.f, 30.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;
	m_tStatus.iPower = 5;
	Update_Rect();
}
