#include "stdafx.h"
#include "Boss01.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "DelayBullet.h"
#include "KeyMgr.h"
#include "BossAlter.h"
#include "Obj.h"
#include "AbstractFactory.h"


CBoss01::CBoss01()
{
}

CBoss01::~CBoss01()
{
	Release();
}

void CBoss01::Initialize()
{
	m_tInfo.vPos = { 300.f, 100.f, 0.f };
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_vLookOrigin = m_tInfo.vLook;

	//���� ���� �»�� ��ǥ 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� ���� ��ǥ. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//���� ���� �� �ϴ�. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// ���� ���� �� �ϴ�. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 3.f;

	m_dwLastAttTime = GetTickCount();

	m_dwPatternTime = 5000;
	m_dwLastPatternChangeTime = GetTickCount();

	m_tStatus.iMaxHp = 20;
	m_tStatus.iHp = m_tStatus.iMaxHp;
	m_tStatus.iPower = 1;

	Set_Pattern(0);
}

int CBoss01::Update()
{
	if (m_bDead) {
		for (int i = 0; i < 50; ++i)
			Die_Effect();

		for (int i = 0; i < m_iAlterCnt; ++i) {
			if (m_pAlter[i])
				m_pAlter[i]->Set_Dead();
		}

		return OBJ_DEAD;
	}

	KeyCheck();
	Pattern();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss01::Late_Update()
{
	if (0 >= m_tStatus.iHp)
		m_bDead = true;
}

void CBoss01::Render(HDC hDC)
{
//	if (m_bTest)
//		TextOut(hDC, 100, 100, L"Test Mode", lstrlen(L"Test Mode"));

	if (m_bAlterMode) return;

	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));
}

void CBoss01::Release()
{
}

int CBoss01::wrap(int x, int low, int high)
{
	assert(low < high);
	const int n = (x - low) % (high - low);
	// �ε��Ҽ��� �ڷ���: const float n = std::fmod(x - low, high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

void CBoss01::KeyCheck()
{
	// ġƮ ���� ����
}

void CBoss01::Pattern()
{
	switch (m_iPattern)
	{
	case 0:
		Pattern00();
		break;
	case 1:
		Pattern01();
		break;
	case 2:
		Pattern02();
		break;
	case 3:
		Pattern03();
		break;
	case 4:
		Pattern04();
		break;
	}
}

void CBoss01::Set_Pattern(int _iPattern)
{
	m_iPattern = _iPattern;
	m_bFirst = true;
	m_iPhase = 0;
}

void CBoss01::Pattern00()
{
	if (m_bFirst) {
		m_tStatus.iHp = m_tStatus.iMaxHp;
		m_dwLastPatternChangeTime = GetTickCount();

		m_bVisible = true;
		m_tInfo.vPos = { 300.f, 100.f, 0.f };
		m_dwAttDelay = 200;

		m_bFirst = false;
	}

	int iCnt = 20 + rand() % 20;
	int iAddAngle = rand() % 360;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		for (int i = 0; i < iCnt; ++i) {
			D3DXMATRIX matRotZ;
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(iAddAngle + i * (360.f / iCnt)));
			D3DXVECTOR3 vDir, vOrigin;
			vOrigin = { 0, 1, 0 };
			D3DXVec3TransformCoord(&vDir, &vOrigin, &matRotZ);

			m_vPosin = m_tInfo.vPos + vDir * m_tInfo.vSize.x;
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBullet>::Create(m_vPosin, vDir));
		}
		m_dwLastAttTime = GetTickCount();
	}

	if (m_tStatus.iHp < m_tStatus.iMaxHp * 0.3f) {
		Set_Pattern(m_iPattern + 1);
	}
}

void CBoss01::Pattern01()
{
	if (m_bFirst)
	{
		AlterMode_On();
		m_tStatus.iHp = m_tStatus.iMaxHp;
		m_dwLastPatternChangeTime = GetTickCount();

		for (int i = 0; i < m_iAlterCnt; ++i) {
			if (m_pAlter[i])
				m_pAlter[i]->Set_Dead();
		}
		for (int i = 0; i < m_iAlterCnt; ++i) {
			m_pAlter[i] = CAbstractFactory<CBossAlter>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y);
			m_pAlter[i]->Set_MaxHp(m_tStatus.iHp);
			m_pAlter[i]->Set_Speed(m_fSpeed);
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, m_pAlter[i]);
		}
		dynamic_cast<CBossAlter*>(m_pAlter[0])->Set_GoalPos(200, m_tInfo.vPos.y + 100);
		dynamic_cast<CBossAlter*>(m_pAlter[1])->Set_GoalPos(WINCX - 200, m_tInfo.vPos.y + 100);

		m_bFirst = false;
	}

	// Alter Mode Attack . . .

	if (!m_bTransition && all_of(m_pAlter, m_pAlter + m_iAlterCnt, [](CObj* pObj) {
		return dynamic_cast<CBossAlter*>(pObj)->Get_GrayMode();
	})) {
		for (int i = 0; i < m_iAlterCnt; ++i) {
			dynamic_cast<CBossAlter*>(m_pAlter[i])->Set_GoalPos(m_tInfo.vPos.x, m_tInfo.vPos.y);
		}
		m_bTransition = true;
	}

	if (m_bTransition) {
		switch (m_iPhase)
		{
		case 0:
			if (all_of(m_pAlter, m_pAlter + m_iAlterCnt, [&](CObj* pObj) {
				return abs(m_tInfo.vPos.x - pObj->Get_Info().vPos.x) < 10;
			})) {
				for (int i = 0; i < m_iAlterCnt; ++i) {
					m_pAlter[i]->Set_Dead();
				}
				AlterMode_Off();
				m_iPhase = 1;
			}
			break;
		case 1:
			m_tInfo.vPos.y -= m_fSpeed;
			if (m_tInfo.vPos.y < -100) {
				m_bTransition = false;
				Set_Pattern(m_iPattern + 1);
			}
			break;
		}
	}
}

void CBoss01::Pattern02()
{
	if (m_bFirst)
	{
		m_bTransition = false;
		m_tStatus.iHp = m_tStatus.iMaxHp;
		m_dwLastPatternChangeTime = GetTickCount();

		m_dwAttDelay = 500;
		m_tInfo.vDir.x = m_fSpeed;
		for (int i = 0; i < 10; ++i) {
			D3DXVECTOR3 vPos = { 100.f + rand() % (WINCX - 200), 100.f + rand() % (WINCY - 200),0.f };
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CDelayBullet>::Create(vPos.x, vPos.y));
		}

		m_bFirst = false;
	}

	if (!m_bTransition &&
		(m_dwLastAttTime + m_dwAttDelay < GetTickCount()))
	{
		D3DXVECTOR3 vPos = { 100.f + rand() % (WINCX - 200), 100.f + rand() % (WINCY - 100),0.f };
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CDelayBullet>::Create(vPos.x, vPos.y));

		m_dwLastAttTime = GetTickCount();
	}

	/*
	if (!m_bTransition &&
		CObjMgr::Get_Instance()->Get_List(OBJID::BOSSBULLET)->empty()) {
		m_bTransition = true;
	}
	*/

	if (!m_bTransition &&
		m_dwLastPatternChangeTime + m_dwPatternTime < GetTickCount()) {
		m_bTransition = true;
	}

	if (m_bTransition) {
		switch (m_iPhase)
		{
		case 0:
			m_tInfo.vPos.y += m_fSpeed;
			if (m_tInfo.vPos.y > 100.f) {
				m_bTransition = false;
				Set_Pattern(m_iPattern + 1);
			}
			break;
		}
	}
}

void CBoss01::Pattern03()
{

}

void CBoss01::Pattern04()
{
}

void CBoss01::AlterMode_On()
{
	m_bAlterMode = true;
	m_bVisible = false;
}

void CBoss01::AlterMode_Off()
{
	m_bAlterMode = false;
	m_bVisible = true;
}
