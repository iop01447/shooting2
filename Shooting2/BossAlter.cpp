#include "stdafx.h"
#include "BossAlter.h"
#include "ObjMgr.h"
#include "Bullet.h"


CBossAlter::CBossAlter()
{
}


CBossAlter::~CBossAlter()
{
}

void CBossAlter::Initialize()
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_vLookOrigin = m_tInfo.vLook;

	m_fSpeed = 0.f;

	m_dwLastAttTime = GetTickCount();
	m_dwAttDelay = 20;

	//원점 기준 좌상단 좌표 
	m_vOrigin[0] = { -m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우상단 좌표. 
	m_vOrigin[1] = { m_tInfo.vSize.x * 0.5f,-m_tInfo.vSize.y * 0.5f, 0.f };
	//원점 기준 우 하단. 
	m_vOrigin[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// 원점 기준 좌 하단. 
	m_vOrigin[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_tStatus.iHp = 10;
}

int CBossAlter::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bTransition)
		Move();
	else
		Attack();

	Check_GrayMode();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossAlter::Late_Update()
{
	if (m_tStatus.iHp < 1 && !m_bGrayMode) {
		m_bGrayMode = true;
		m_dwLastGrayOnTime = GetTickCount();
	}
}

void CBossAlter::Render(HDC hDC)
{
	D3DXMATRIX matScale, matRotZ, matTrance;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrance, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrance;

	HPEN hOldPen{ NULL };
	if (m_bGrayMode) {
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(125, 125, 125));
		hOldPen = (HPEN)SelectObject(hDC, hPen);
	}

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOrigin[i], &m_tInfo.matWorld);

	MoveToEx(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y), nullptr);

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, int(m_vPoint[i].x), int(m_vPoint[i].y));

	LineTo(hDC, int(m_vPoint[0].x), int(m_vPoint[0].y));

	if (m_bGrayMode) {
		SelectObject(hDC, hOldPen);
	}
}

void CBossAlter::Release()
{
}

void CBossAlter::Move()
{
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	if (abs(m_tInfo.vPos.x - m_vGoalPos.x) < 10) {
		m_tInfo.vPos = m_vGoalPos;
		m_bTransition = false;
	}
}

void CBossAlter::Attack()
{
	if (m_bGrayMode) return;

	m_fAngle += m_fAddAngle;
	if (m_fAngle > 30 || m_fAngle < -30)
		m_fAddAngle *= -1;

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

void CBossAlter::Set_GoalPos(float _fX, float _fY)
{
	m_vGoalPos = { _fX, _fY, 0 };
	D3DXVECTOR3 vDir = m_vGoalPos - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &vDir);

	m_bTransition = true;
}

void CBossAlter::Check_GrayMode()
{
	if (m_bTransition) return;
	if (m_bGrayMode &&
		m_dwGrayTime + m_dwLastGrayOnTime < GetTickCount()) {
		m_tStatus.iHp = m_tStatus.iMaxHp;
		m_bGrayMode = false;
	}
}
