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
	m_tInfo.vSize.x = 10.f;
	m_tInfo.vSize.y = 30.f;
	m_fSpeed = 5.f;

	Update_Rect();
}
