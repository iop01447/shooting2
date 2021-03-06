#include "stdafx.h"
#include "Boss00.h"

#include "ObjMgr.h"
#include "Boss00Bullet1.h"
#include "Boss00Bullet2.h"
#include "Razer.h"

CBoss00::CBoss00()
{
	ZeroMemory(m_pRazer, sizeof(m_pRazer));
}


CBoss00::~CBoss00()
{
	Release();
}

void CBoss00::Initialize()
{
	m_tInfo.vPos = { 300.f, 120.f, 0.f };
	m_tInfo.vSize = { 100.f, 100.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_vOriginPosin[0] = { 0.f, (0.f + m_tInfo.vSize.y / 2 + 10.f), 0.f };
	m_vOriginPosin[1] = { -m_tInfo.vSize.x * 0.4f, (0.f + m_tInfo.vSize.y / 2 + 10.f), 0.f };
	m_vOriginPosin[2] = { m_tInfo.vSize.x * 0.4f, (0.f + m_tInfo.vSize.y / 2 + 10.f), 0.f };
	memcpy(&m_vStart, &m_tInfo.vPos, sizeof(m_vStart));

	for (int i = 0; i < 2; ++i)
	{
		m_vOriginRazer[i][0] = { m_vOriginPosin[i + 1].x - 7.f ,m_vOriginPosin[i + 1].y - 10.f, 0.f };
		m_vOriginRazer[i][1] = { m_vOriginPosin[i + 1].x + 7.f ,m_vOriginPosin[i + 1].y - 10.f, 0.f };
		m_vOriginRazer[i][2] = { m_vOriginPosin[i + 1].x + 7.f ,m_vOriginPosin[i + 1].y - 10.f, 0.f };
		m_vOriginRazer[i][3] = { m_vOriginPosin[i + 1].x - 7.f ,m_vOriginPosin[i + 1].y - 10.f, 0.f };
	}

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 2.f;
	m_dwAttDelay = 3000;
	m_dwAttTime = 5000;
	m_dwLastAttTime = GetTickCount();

	m_eState = IDLE;
	m_eDir = DIR_END;
	m_iCount = 0;
	m_iPatton = -1;

	m_tStatus.iMaxHp = 100;
	m_tStatus.iHp = m_tStatus.iMaxHp;

	m_listBullet = CObjMgr::Get_Instance()->Get_List(OBJID::BULLET);
}

int CBoss00::Update()
{
	if (m_bDead)
	{
		for (int i = 0; i < 50; ++i)
			Die_Effect();
		return OBJ_DEAD;
	}

	if (m_bStart)
	{
		if (m_dwStartTime + (m_dwStartDelay / 2) < GetTickCount())
			m_bStart = false;

		D3DXMATRIX matScale, matRotZ, matTrance;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrance;

		for (int i = 0; i < 4; ++i)
			D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

		return OBJ_NOEVENT;
	}

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss00::Late_Update()
{
	if (0 >= m_tStatus.iHp)
		m_bDead = true;
}

void CBoss00::Render(HDC hDC)
{
	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	for (int i = 0; i < 3; ++i)
		D3DXVec3TransformCoord(&m_vPosin[i], &m_vOriginPosin[i], &m_tInfo.matWorld);

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			D3DXVec3TransformCoord(&m_vRazer[i][j], &m_vOriginRazer[i][j], &m_tInfo.matWorld);

	MoveToEx(hDC, int(m_vPoint[3].x), int(m_vPoint[3].y), nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	if (ATTACK3 == m_eState)
	{
		for (int i = 0; i < 2; ++i)
		{
			MoveToEx(hDC, int(m_vRazer[i][3].x), int(m_vRazer[i][3].y), nullptr);
			for (int j = 0; j < 4; ++j)
			{
				LineTo(hDC, int(m_vRazer[i][j].x), int(m_vRazer[i][j].y));
			}
		}
	}
}

void CBoss00::Release()
{
}

void CBoss00::Move()
{
	if (360 == m_fAngle)
		m_fAngle = 0.f;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		if (IDLE == m_eState)
			m_eState = ATTACK;
		Attack();
		//return;
	}

	if (ATTACK1 != m_eState && 0 != m_fAngle)
	{
		if (180 > m_fAngle)
			m_fAngle -= 5.f;
		else
			m_fAngle += 5.f;
	}

	if (START == m_eState)
	{
		BackStartPos();
		//return;
	}

	int iCount = 0;
	for (auto pBullet : *m_listBullet)
	{
		if (pBullet->Get_Info().vPos.y > m_tInfo.vPos.y)
		{
			++iCount;
			if (150 > m_tInfo.vPos.x && RIGHT == m_eDir)
				break;
			else if (WINCX - 150 < m_tInfo.vPos.x && LEFT == m_eDir)
				break;

			if (m_tInfo.vSize.x - 30.f > abs(pBullet->Get_Info().vPos.x - m_tInfo.vPos.x))
			{
				if (pBullet->Get_Info().vPos.x > m_tInfo.vPos.x)
					m_eDir = LEFT;
				else
					m_eDir = RIGHT;
			}
			else
			{
				m_eDir = DIR_END;
				continue;
			}

			if (80 > m_tInfo.vPos.x)
				m_eDir = RIGHT;
			else if (WINCX - 80 < m_tInfo.vPos.x)
				m_eDir = LEFT;

			break;
		}

		if (5 < iCount)
			break;
	}

	switch (m_eDir)
	{
	case CBoss00::LEFT:
		m_tInfo.vPos.x -= (m_fSpeed * 1.5f);
		break;
	case CBoss00::RIGHT:
		m_tInfo.vPos.x += (m_fSpeed * 1.5f);
		break;
	case CBoss00::DIR_END:
		break;
	default:
		break;
	}
}

void CBoss00::Attack()
{
	if (ATTACK == m_eState)
	{
		++m_iPatton;
		if (2 < m_iPatton)
			m_iPatton = 0;

		switch (m_iPatton)
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
		default:
			break;
		}
	}
	
	switch (m_eState)
	{
	case CBoss00::ATTACK1:
		Attack1();
		break;
	case CBoss00::ATTACK2:
		Attack2();
		break;
	case CBoss00::ATTACK3:
		Attack3();
		break;
	default:
		break;
	}
}

void CBoss00::Attack1()
{
	if (ATTACK != m_eState && ATTACK1 != m_eState)
		return;

	m_eState = ATTACK1;

	m_tInfo.vPos.y += m_fSpeed;

	m_fAngle += 5.f;

	m_tInfo.vDir = m_vPosin[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	for (int i = 0; i < 3; ++i)
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss00Bullet1>(m_vPosin[i], m_tInfo.vDir));

	if (m_dwLastAttTime + m_dwAttTime < GetTickCount())
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = START;
	}
}

void CBoss00::Attack2()
{
	if (ATTACK != m_eState && ATTACK2 != m_eState)
		return;

	m_eState = ATTACK2;

	D3DXVECTOR3 vDir = m_vPosin[0] - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);// acosf 0~ ㅠ

	if (m_tInfo.vPos.y < m_vPosin[0].y)
		fAngle *= -1.f;

	if (m_dwLastAttTime + m_dwAttTime + 500 > GetTickCount())
	{
		if (0 == m_iCount)
		{
			float fAng = -0.6f;
			for (int i = 0; i < 7; ++i)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss00Bullet1>(m_vPosin[0].x, m_vPosin[0].y, fAngle + fAng));
				fAng += 0.2f;
			}
		}
		else if (10 == m_iCount)
		{
			float fAng = -0.5f;
			for (int i = 0; i < 6; ++i)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss00Bullet1>(m_vPosin[0].x, m_vPosin[0].y, fAngle + fAng));
				fAng += 0.2f;
			}
		}
	}

	if (m_dwLastAttTime + m_dwAttTime - 200 < GetTickCount())
	{
		if (0 == m_iCount % 10)
		{
			for (int i = 1; i < 3; ++i)
			{
				D3DXVECTOR3 vDir = m_pTarget->Get_Info().vPos - m_vPosin[i];
				D3DXVec3Normalize(&vDir, &vDir);
				fDot = D3DXVec3Dot(&vDir, &m_tInfo.vLook);

				fAngle = acosf(fDot);// acosf 0~ ㅠ

				if (m_vPosin[i].y < m_pTarget->Get_Info().vPos.y)
					fAngle *= -1.f;
				CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, Create_Bullet<CBoss00Bullet2>(m_vPosin[i], vDir));
			}
		}
	}

	if (m_dwLastAttTime + (m_dwAttTime * 1.7f) < GetTickCount())
	{
		m_dwLastAttTime = GetTickCount();
		m_eState = START;
		m_iCount = 0;
	}

	++m_iCount;
	if (20 <= m_iCount)
		m_iCount = 0;
}

void CBoss00::Attack3()
{
	if (m_dwLastAttTime + m_dwAttTime + 2000 < GetTickCount())
	{
		if (m_vOriginPosin[0].y != m_vOriginRazer[0][2].y)
		{
			for (int i = 0; i < 2; ++i)
				for (int j = 2; j < 4; ++j)
					m_vOriginRazer[i][j].y -= 1.f;
			return;
		}
		m_dwLastAttTime = GetTickCount();
		m_eState = IDLE;
		m_iCount = 0;
		for (int i = 0; i < 2; ++i)
			m_pRazer[i] = nullptr;
		return;
	}

	if (m_vOriginPosin[0].y + 50.f > m_vOriginRazer[0][2].y)
	{
		for (int i = 0; i < 2; ++i)
			for (int j = 2; j < 4; ++j)
				m_vOriginRazer[i][j].y += 2.f;

		return;
	}

	if (20 == m_iCount)
		for (int i = 0; i < 2; ++i)
		{
			m_pRazer[i] = Create_Bullet<CRazer>(m_vRazer[i][0].x + 7.f, m_vRazer[i][2].y + 10.f);
			m_pRazer[i]->Set_Target(this);
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, m_pRazer[i]);
		}

	++m_iCount;

	for (int i = 0; i < 2; ++i)
		if (m_pRazer[i])
			dynamic_cast<CRazer*>(m_pRazer[i])->Set_PosX(m_vRazer[i][0].x + 7.f);
}

void CBoss00::BackStartPos()
{
	m_tInfo.vDir = m_vStart - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < m_vStart.y)
		fAngle *= -1.f;

	if (0 > fAngle || 180 < fAngle)
	{
		m_eState = IDLE;
		return;
	}

	//m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	//m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= m_fSpeed;

	m_dwLastAttTime = GetTickCount();
}
