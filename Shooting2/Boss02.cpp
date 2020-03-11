#include "stdafx.h"
#include "Boss02.h"
#include "Boss02Bullet.h"
#include "RotBullet.h"
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

	//À­Á¡
	m_vOrigin[0] = {};
	//¿ìÇÏ´Ü
	m_vOrigin[1] = {};
	//ÁÂÇÏ´Ü
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
	m_dwBulletTime2 = 100;
	m_eState = IDLE;
	m_ePhase = PHASE1;
	m_bDir = true;
	m_vDir = {1, 1, 0};
}

int CBoss02::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bStart)
	{
		if (m_dwStartTime + (m_dwStartDelay * 2) < GetTickCount())
			m_bStart = false;

		return OBJ_NOEVENT;
	}

	//Ç®ÇÇ
	if (80 < m_tStatus.iHp)
		m_ePhase = PHASE1;
	//»ï°¢
	else if(60 < m_tStatus.iHp)
		m_ePhase = PHASE2;
	//»ç°¢
	else if (40 < m_tStatus.iHp)
		m_ePhase = PHASE3;
	//¿À°¢
	else if (20 < m_tStatus.iHp)
		m_ePhase = PHASE4;
	//À°°¢
	else if (00 < m_tStatus.iHp)
		m_ePhase = PHASE5;

	if (m_ePhase == PHASE2)
	{
		//Áß¾Ó»ó´Ü
		m_vOrigin[0] = { 0,-m_tInfo.vSize.y * 0.5f, 0.f };
		//¿ìÇÏ´Ü
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		//ÁÂÇÏ´Ü
		m_vOrigin[2] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
	}
	// »ç°¢
	else if (m_ePhase == PHASE3)
	{
		//ÁÂ»ó´Ü
		m_vOrigin[0] = { -m_tInfo.vSize.x* 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
		//¿ì»ó´Ü
		m_vOrigin[1] = { +m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
		//¿ìÇÏ´Ü
		m_vOrigin[2] = { +m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//ÁÂÇÏ´Ü
		m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	}

	// ¿À°¢
	else if (m_ePhase == PHASE4)
	{
		//Áß¾Ó»ó´Ü
		m_vOrigin[0] = { 0,-m_tInfo.vSize.y * 0.5f, 0.f };
		//¿ìÁß´Ü
		m_vOrigin[1] = { m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(18.f)), -m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(18.f)), 0.f };
		//¿ìÇÏ´Ü
		m_vOrigin[2] = { +m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(54.f)), m_tInfo.vSize.y * 0.5f* sinf(D3DXToRadian(54.f)), 0.f };
		//ÁÂÇÏ´Ü
		//m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, +m_tInfo.vSize.y * 0.5f, 0.f };
		m_vOrigin[3] = { -m_tInfo.vSize.x *0.5f * cosf(D3DXToRadian(54.f)), m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(54.f)), 0.f };
		//ÁÂÁß´Ü
		m_vOrigin[4] = { -m_tInfo.vSize.x* 0.5f * cosf(D3DXToRadian(18.f)), -m_tInfo.vSize.y * 0.5f * sinf(D3DXToRadian(18.f)), 0.f };
	}

	// À°°¢
	else if (m_ePhase == PHASE5)
	{
		//ÁÂ»ó´Ü
		m_vOrigin[0] = { -m_tInfo.vSize.x* 0.5f* 0.5f  ,-m_tInfo.vSize.y* 0.5f , 0.f };
		//¿ì»ó´Ü
		m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f* 0.5f, -m_tInfo.vSize.y* 0.5f , 0.f };
		//¿ìÁß´Ü
		m_vOrigin[2] = { m_tInfo.vSize.x* 0.5f ,0, 0.f };
		//¿ìÇÏ´Ü
		m_vOrigin[3] = { m_tInfo.vSize.x* 0.5f* 0.5f, m_tInfo.vSize.y* 0.5f , 0.f };
		//ÁÂÇÏ´Ü
		m_vOrigin[4] = { -m_tInfo.vSize.x* 0.5f  *0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
		//ÁÂÁß´Ü
		m_vOrigin[5] = { -m_tInfo.vSize.x* 0.5f ,0, 0.f };
	}
	if (m_bDead)
		return OBJ_DEAD;

	Move();


	//if (m_ePhase == PHASE1)
	//	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);
	//else if (m_ePhase == PHASE2)
	//	D3DXMatrixScaling(&matScale, 1.4f, 1.4f, 0.f);
	//else if (m_ePhase == PHASE3)
	//	D3DXMatrixScaling(&matScale, 1.3f, 1.3f, 0.f);
	//else if (m_ePhase == PHASE4)
	//	D3DXMatrixScaling(&matScale, 1.2f, 1.2f, 0.f);
	//else if (m_ePhase == PHASE5)
	//	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

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
	if (0 >= m_tStatus.iHp)
		m_bDead = true;
}

void CBoss02::Render(HDC hDC)
{
	// ¿ø
	if (m_ePhase == PHASE1)
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	// »ï°¢
	else if (m_ePhase == PHASE2)
	{
		MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);
		for (int i = 1; i < 3; ++i)
		{
			LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));
		}
		LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
	}
	// »ç°¢
	else if (m_ePhase == PHASE3)
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
	// ¿À°¢
	else if (m_ePhase == PHASE4)
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
	// À°°¢
	else if (m_ePhase == PHASE5)
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
	if (361 <= m_fAngle)
		m_fAngle = 0.f;
	
	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		if (IDLE == m_eState)
			m_eState = ATTACK;
		Attack();
		return;
	}
	if (m_tRect.left <= 0 || m_tRect.right >= WINCX)
	{
		m_vDir.x *= -1;
	}
	if (m_tRect.bottom >= WINCY/2 || m_tRect.top <= 0)
	{
		m_vDir.y *= -1;
	}
	m_tInfo.vPos += m_vDir;
	
	//if (0 != m_fAngle)
	//{
	//	if (180 > m_fAngle)
	//		m_fAngle -= 3.f;
	//	else
	//		m_fAngle += 3.f;
	//}

	if (START == m_eState)
	{
		//BackStartPos();
		return;
	}
}

void CBoss02::Attack()
{
	if (m_bDir)
		m_fAngle += 3.f;
	else
		m_fAngle -= 3.f;
	
	if (ATTACK == m_eState)
	{
		int r = rand() % 5;

		switch (r)
		{
		case 0:
			m_eState = ATTACK1;
			break;
		case 1:
			m_eState = ATTACK2;
			break;
		case 2:
			m_eState = ATTACK3;
			break;
		case 3:
			m_eState = ATTACK4;
			break;
		case 4:
			m_eState = ATTACK5;
			break;
		default:
			break;
		}
	}

	switch (m_eState)
	{
	case CBoss02::ATTACK1:
		Attack1();
		break;
	case CBoss02::ATTACK2:
		Attack2();
		break;
	case CBoss02::ATTACK3:
		Attack3();
		break;
	case CBoss02::ATTACK4:
		Attack4();
		break;
	case CBoss02::ATTACK5:
		Attack5();
		break;
	default:
		break;
	}

	//if (m_bDir)
	//	m_fAngle += 3.f;
	//else
	//	m_fAngle -= 3.f;
	//	Attack1();
	//	Attack2();
	//	Attack3();
	//	Attack4();
}

void CBoss02::Attack1()
{
	//if (ATTACK != m_eState && ATTACK1 != m_eState)
	//	return;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ¤Ð

	if (m_tInfo.vPos.y < m_vPoint[0].y)
		fAngle *= -1.f;

	if (m_ePhase == PHASE1)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, m_fAngle));
	}
	else if(m_ePhase == PHASE2)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, m_fAngle));
		
	}
	else if (m_ePhase == PHASE3)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[2].x, m_vPoint[2].y, m_fAngle));
	}
	else if (m_ePhase == PHASE4)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, m_fAngle));
		
	}
	else if (m_ePhase == PHASE5)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[2].x, m_vPoint[2].y, m_fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[4].x, m_vPoint[4].y, m_fAngle));
	}


	if (m_fAngle>=360|| m_fAngle<=-360)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_bDir = !m_bDir;
		m_fAngle = 0;
	}
}

void CBoss02::Attack2()
{
	//if (ATTACK != m_eState && ATTACK2 != m_eState)
	//	return;
	//m_eState = ATTACK2;
	if (m_bDir)
		m_fAngle += 3.f;
	else
		m_fAngle -= 3.f;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ¤Ð
	float fAngle2 = acosf(-fDot);
	if (m_tInfo.vPos.y < m_vPoint[0].y)
	{
		fAngle *= -1.f;
		fAngle2 *= -1.f;
	}


	if (m_ePhase == PHASE1)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle));
	
	}
	else if (m_ePhase == PHASE2)
	{
		//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle));	
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[1].x, m_vPoint[1].y, fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[2].x, m_vPoint[2].y, fAngle2));
	}
	else if (m_ePhase == PHASE3)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[1].x, m_vPoint[1].y, fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[3].x, m_vPoint[3].y, fAngle2));
	}
	else if (m_ePhase == PHASE4)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, fAngle));

	}
	else if (m_ePhase == PHASE5)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, fAngle));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[0].x, m_vPoint[0].y, fAngle2));
		//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[2].x, m_vPoint[2].y, fAngle));
		//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[3].x, m_vPoint[3].y, fAngle2));
		//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[4].x, m_vPoint[4].y, fAngle));
		//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_vPoint[5].x, m_vPoint[5].y, fAngle2));
		
	}

	if (m_fAngle >= 360 || m_fAngle <= -360)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_bDir = !m_bDir;
		m_fAngle = 0;
	}
}

void CBoss02::Attack3()
{
	//if (ATTACK != m_eState && ATTACK3 != m_eState)
	//	return;
	//m_eState = ATTACK3;
	//if (m_bDir)
	//	m_fAngle += 3.f;
	//else
	//	m_fAngle -= 3.f;

	D3DXVECTOR3 vDir = m_vPoint[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ¤Ð

	if (m_tInfo.vPos.y < m_vPoint[0].y)
		fAngle *= -1.f;

	if (m_dwBulletTime + 100 < GetTickCount())
	{
		if (m_ePhase == PHASE1)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, D3DXToRadian(270)));

		}
		else if (m_ePhase == PHASE2)
		{	
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x + m_tInfo.vSize.x / 2, m_tInfo.vPos.y, D3DXToRadian(270)));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x - m_tInfo.vSize.x / 2, m_tInfo.vPos.y, D3DXToRadian(270)));
		}
		else if (m_ePhase == PHASE3)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, D3DXToRadian(270)));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x + m_tInfo.vSize.x / 2, m_tInfo.vPos.y, D3DXToRadian(270)));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x - m_tInfo.vSize.x / 2, m_tInfo.vPos.y, D3DXToRadian(270)));

		}
		else if (m_ePhase == PHASE4)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, D3DXToRadian(270)));
		}
		else if (m_ePhase == PHASE5)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, D3DXToRadian(270)));
		}
		m_dwBulletTime = GetTickCount();
	}
	if (m_fAngle >= 360 || m_fAngle <= -360)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_bDir = !m_bDir;
		m_fAngle = 0;
	}


}

void CBoss02::Attack4()
{
	//if (ATTACK != m_eState && ATTACK4 != m_eState)
	//	return;

	D3DXVECTOR3 vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ¤Ð

	if (m_tInfo.vPos.y < m_pTarget->Get_Info().vPos.y)
		fAngle *= -1.f;
	if (m_dwBulletTime2 + 100 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle + 0.1f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle - 0.1f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle + 0.2f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle - 0.2f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle + 0.3f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle - 0.3f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle + 0.4f));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss02Bullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, fAngle - 0.4f));
		m_dwBulletTime2 = GetTickCount();
	}
	if (m_fAngle >= 360 || m_fAngle <= -360)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_bDir = !m_bDir;
		m_fAngle = 0;
	}
}

void CBoss02::Attack5()
{

	D3DXVECTOR3 vDir[6] = {};
	for (int i = 0; i < 6; i++)
	{
		vDir[i] = m_vPoint[i] - m_tInfo.vPos;
		D3DXVec3Normalize(&vDir[i], &vDir[i]);
	}




	// acosf 0~ ¤Ð
	//float fAngle1 = asinf(fDot);
	//if (m_tInfo.vPos.y < m_vPoint[0].y)
	//{
	//	fAngle *= -1.f;
	//	//fAngle1 *= -1.f;
	//}
	for (size_t i = 0; i < 6; i++)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CRotBullet>(m_vPoint[i], vDir[i]));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CRotBullet>(m_vPoint[i], vDir[i]));
	}
	if (m_fAngle >= 360 || m_fAngle <= -360)
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_bDir = !m_bDir;
		m_fAngle = 0;
	}
}
