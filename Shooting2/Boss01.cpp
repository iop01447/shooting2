#include "stdafx.h"
#include "Boss01.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "DelayBullet.h"
#include "KeyMgr.h"


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

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fAngle = 0.f;
	m_fSpeed = 5.f;

	m_dwLastAttTime = GetTickCount();

	m_dwPatternTime = 5000;
	m_dwLastPatternChangeTime = GetTickCount();

	InitPattern();
}

int CBoss01::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	KeyCheck();

	Pattern();
	if(!m_bTest)
		Change_Pattern();

	Update_Matrix();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss01::Late_Update()
{
}

void CBoss01::Render(HDC hDC)
{
	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	if (m_bTest)
		TextOut(hDC, 100, 100, L"Test Mode", lstrlen(L"Test Mode"));
}

void CBoss01::Release()
{
}

int CBoss01::wrap(int x, int low, int high)
{
	assert(low < high);
	const int n = (x - low) % (high - low);
	// 부동소수점 자료형: const float n = std::fmod(x - low, high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

void CBoss01::KeyCheck()
{
	if(CKeyMgr::Get_Instance()->Key_Down('T')) {
		m_bTest = !m_bTest;
	}
	if (!m_bTest) return;

	for (int i = 0; i < m_iMaxPattern; ++i) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD0 + i)) {
			m_iPattern = i;
			InitPattern();
			return;
		}
	}
}

void CBoss01::Update_Matrix()
{
	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);
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
	}
}

void CBoss01::Change_Pattern()
{
	if (m_dwLastPatternChangeTime + m_dwPatternTime > GetTickCount()) return;
		
	m_iPattern = (m_iPattern + 1) % m_iMaxPattern;
	m_dwLastPatternChangeTime = GetTickCount();

	InitPattern();
}

void CBoss01::InitPattern()
{
	switch (m_iPattern)
	{
	case 0:
		m_dwAttDelay = 20;
		break;
	case 1:
		m_dwAttDelay = 200;
		break;
	case 2:
		m_dwAttDelay = 1000;
		m_tInfo.vDir.x = m_fSpeed;
		for (int i = 0; i < 10; ++i) {
			D3DXVECTOR3 vPos = { 100.f + rand() % (WINCX - 200), 100.f + rand() % (WINCY - 200),0.f };
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CDelayBullet>::Create(vPos.x, vPos.y));
		}
		break;
	}
}

void CBoss01::Pattern00()
{
	static float fAddAngle = 3;
	m_fAngle += fAddAngle;
	if (m_fAngle > 30 || m_fAngle < -30)
		fAddAngle *= -1;

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXVec3TransformCoord(&m_tInfo.vLook, &m_vLookOrigin, &matRotZ);

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		m_vPosin = m_tInfo.vPos + m_tInfo.vLook * m_tInfo.vSize.x;
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBullet>::Create(m_vPosin, m_tInfo.vLook));
		m_dwLastAttTime = GetTickCount();
	}
}

void CBoss01::Pattern01()
{
	int iCnt = 20 + rand() % 20;
	int iAddAngle = rand() % 360;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		for (int i = 0; i < iCnt; ++i) {
			D3DXMATRIX matRotZ;
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(iAddAngle + i * (360.f/iCnt)));
			D3DXVECTOR3 vDir, vOrigin;
			vOrigin = { 0, 1, 0 };
			D3DXVec3TransformCoord(&vDir, &vOrigin, &matRotZ);

			m_vPosin = m_tInfo.vPos + vDir * m_tInfo.vSize.x;
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBullet>::Create(m_vPosin, vDir));
		}
		m_dwLastAttTime = GetTickCount();
	}
}

void CBoss01::Pattern02()
{
	m_tInfo.vPos.x += m_tInfo.vDir.x;
	if (m_tInfo.vPos.x > WINCX - 100 || m_tInfo.vPos.x < 100)
		m_tInfo.vDir.x *= -1;

	if (m_dwLastAttTime + m_dwAttDelay < GetTickCount())
	{
		D3DXVECTOR3 vPos = { 100.f + rand() % (WINCX - 200), 100.f + rand() % (WINCY - 100),0.f };
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CDelayBullet>::Create(vPos.x, vPos.y));

		m_dwLastAttTime = GetTickCount();
	}
}
