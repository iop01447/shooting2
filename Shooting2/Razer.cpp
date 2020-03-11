#include "stdafx.h"
#include "Razer.h"
#include "Boss00.h"

#include "ObjMgr.h"
#include "SmallBullet.h"

CRazer::CRazer()
{
}


CRazer::~CRazer()
{
	Release();
}

void CRazer::Initialize()
{
	m_tInfo.vSize = { 30.f, 20.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };

	m_fSpeed = 20.f;

	m_dwAttTime = 800;
	m_dwDeltaTime = GetTickCount();

	m_iRenderIdx = 1;

	Update_Rect();
}

int CRazer::Update()
{
	if (0 > m_tRect.top || WINCY < m_tRect.top)
	{
		for (auto pObj : m_listBullet)
		{
			pObj->Set_Dead();
		}
		return OBJ_DEAD;
	}

	if (m_pTarget)
	{
		if (m_pTarget->Get_Dead())
		{
			for (auto pObj : m_listBullet)
			{
				pObj->Set_Dead();
			}
			return OBJ_DEAD;
		}
	}

	if (WINCY * 1.5f > m_tRect.bottom)
	{
		m_tRect.bottom += (LONG)(m_fSpeed / 2);
		CObj* pObj = Create_Bullet<CSmallBullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, m_fAngle);
		pObj->Set_Target(this);
		m_listBullet.emplace_back(pObj);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
		m_dwDeltaTime = GetTickCount();
	}
	else if (m_dwDeltaTime + m_dwAttTime < GetTickCount())
	{
		m_tRect.top += (LONG)(m_fSpeed / 2 - 2.5f);
		dynamic_cast<CBoss00*>(m_pTarget)->Set_Razer();
	}
	else
	{
		CObj* pObj = Create_Bullet<CSmallBullet>(m_tInfo.vPos.x, m_tInfo.vPos.y, m_fAngle);
		pObj->Set_Target(this);
		m_listBullet.emplace_back(pObj);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
	}

	m_tRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x / 2));
	m_tRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x / 2));

	return OBJ_NOEVENT;
}

void CRazer::Late_Update()
{
}

void CRazer::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRazer::Release()
{
}