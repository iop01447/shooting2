#include "stdafx.h"
#include "Boss02.h"
#include "Boss02Bullet.h"
#include "ObjMgr.h"

CBoss02::CBoss02()
{
}


CBoss02::~CBoss02()
{
	Release();
}

void CBoss02::Initialize()
{
	m_tInfo.vPos = { 300.f, 100.f, 0.f };
	m_tInfo.vSize = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//윗점
	m_vOrigin[0] = {};
	//우하단
	m_vOrigin[1] = {};
	//좌하단
	m_vOrigin[2] = {};

	m_vOrigin[3] = {};
	m_vOrigin[4] = {};
	m_vOrigin[5] = {};


	m_fAngle = 0.f;
	m_fSpeed = 5.f;

	m_tStatus.iHp = 100;

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_dwAttDelay = 1000;
	m_dwAttTime = 3000;
	m_dwLastAttTime = GetTickCount();
	m_dwBulletTime = 100;
	m_eState = IDLE;
}

int CBoss02::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (60 <= m_tStatus.iHp)
	{
		//중앙상단
		m_vOrigin[0] = { 0,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
	}
	// 사각
	else if (40 <= m_tStatus.iHp)
	{
		//좌상단
		m_vOrigin[0] = { -m_tInfo.vSize.x* 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우상단
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
		//우하단
		m_vOrigin[2] = { +m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//좌하단
		m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	}

	// 오각
	else if (20 <= m_tStatus.iHp)
	{
		//중앙상단
		m_vOrigin[0] = {0,-m_tInfo.vSize.y * 0.5f, 0.f };
		//우중단
		m_vOrigin[1] = { m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(18.f)), -m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(18.f)), 0.f };
		//우하단
		m_vOrigin[2] = { +m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(54.f)), m_tInfo.vSize.y * 0.5f* sinf(D3DXToRadian(54.f)), 0.f };
		//좌하단
		//m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		m_vOrigin[3] = { -m_tInfo.vSize.x *0.5f * cosf(D3DXToRadian(54.f)), m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(54.f)), 0.f };
		//좌중단
		m_vOrigin[4] = { -m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(18.f)), -m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(18.f)), 0.f };
	}

	// 육각
	else if (0 <= m_tStatus.iHp)
	{
		//좌상단
		m_vOrigin[0] = { -m_tInfo.vSize.x* 0.5f* 0.5f  ,-m_tInfo.vSize.y* 0.5f , 0.f };
		//우상단
		m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f* 0.5f, -m_tInfo.vSize.y* 0.5f , 0.f };
		//우중단
		m_vOrigin[2] = { m_tInfo.vSize.x* 0.5f ,0, 0.f };
		//우하단
		m_vOrigin[3] = { m_tInfo.vSize.x* 0.5f* 0.5f, m_tInfo.vSize.y* 0.5f , 0.f };
		//좌하단
		m_vOrigin[4] = {- m_tInfo.vSize.x* 0.5f  *0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//좌중단
		m_vOrigin[5] = {-m_tInfo.vSize.x* 0.5f ,0, 0.f };
	}
	if (m_bDead)
		return OBJ_DEAD;

	Move();

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 6; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	

	return OBJ_NOEVENT;
}

void CBoss02::Late_Update()
{
	Update_Rect();
}

void CBoss02::Render(HDC hDC)
{
	// 원
	if (80 <= m_tStatus.iHp)
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	// 삼각
	else if (60 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 3; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}
	// 사각
	else if (40 <= m_tStatus.iHp)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 4; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
		
		MoveToEx(hDC, int(m_vPoint[1].x), int(m_vPoint[1].y), nullptr);
		LineTo(hDC, int(m_vPoint[3].x), int(m_vPoint[3].y));
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		LineTo(hDC, int(m_vPoint[2].x), int(m_vPoint[2].y));

	}
	// 오각
	else if (20 <= m_tStatus.iHp)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = i; j < 5; ++j)
			{
				MoveToEx(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y), nullptr);
				LineTo(hDC, int(m_vPoint[j].x), int(m_vPoint[j].y));

			}
		}
	}

	// 육각
	else if (0 <= m_tStatus.iHp)
	{
		

		for (int i = 0; i < 6; ++i)
		{
			for (int j = i; j < 6; ++j)
			{
				MoveToEx(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y), nullptr);
				LineTo(hDC, int(m_vPoint[j].x), int(m_vPoint[j].y));

			}
		}
	}

}

void CBoss02::Release()
{
}

void CBoss02::Move()
{
	if (360 == m_fAngle)
		m_fAngle = 0.f;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		if (IDLE == m_eState)
			m_eState = ATTACK;
		Attack();
		return;
	}

	if (0 != m_fAngle)
	{
		if (180 > m_fAngle)
			m_fAngle -= 3.f;
		else
			m_fAngle += 3.f;
	}

	if (START == m_eState)
	{
		//BackStartPos();
		return;
	}
}

void CBoss02::Attack()
{
	
}

void CBoss02::Attack1()
{
	if(ATTACK != m_eState && ATTACK1 != m_eState)
		return;
	m_eState = ATTACK1;
	m_fAngle += 3.f;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ㅠ

	if (m_tInfo.vPos.y < m_vPoint[0].y)
		fAngle *= -1.f;

	m_fAngle += 0.4f;
	CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, m_fAngle));
	
	if (m_dwLastAttTime + m_dwAttTime < GetTickCount())
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
	}
}

void CBoss02::Attack2()
{
	if (ATTACK != m_eState && ATTACK2 != m_eState)
		return;
	m_eState = ATTACK2;
	m_fAngle += 3.f;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ㅠ

	if (m_tInfo.vPos.y < m_vPoint[0].y)
		fAngle *= -1.f;
	//제어용
	//fAngle *= -4.f;
	
	m_fAngle += 3.f;
	CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle));
	//CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y,D3DXToRadian(270)));
	if (/*m_dwLastAttTime + m_dwAttTime < GetTickCount() ||*/ 360 == m_fAngle)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
	}
}

void CBoss02::Attack3()
{
	if (ATTACK != m_eState && ATTACK3 != m_eState)
		return;
	m_eState = ATTACK3;
	m_fAngle += 3.f;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ㅠ

	if (m_tInfo.vPos.y < m_vPoint[0].y)
		fAngle *= -1.f;
	int iCount = 0;
	if (m_dwBulletTime + 100 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, D3DXToRadian(270)));
		m_dwBulletTime = GetTickCount();
	}
	if (m_dwLastAttTime + m_dwAttTime < GetTickCount())
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		
	}


}
