#include "stdafx.h"
#include "Boss00Bullet2.h"


CBoss00Bullet2::CBoss00Bullet2()
{
}


CBoss00Bullet2::~CBoss00Bullet2()
{
}

void CBoss00Bullet2::Initialize()
{
	m_tInfo.vSize = { 10.f, 30.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };

	m_fSpeed = 5.f;
	m_tStatus.iPower = 5;

	Update_Rect();
}

int CBoss00Bullet2::Update()
{
	return 0;
}

void CBoss00Bullet2::Late_Update()
{
}

void CBoss00Bullet2::Render(HDC hDC)
{
}

void CBoss00Bullet2::Release()
{
}
