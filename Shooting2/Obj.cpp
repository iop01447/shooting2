#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_bDead(false), m_eGroup(GROUPID::GAMEOBJECT), m_iRenderIdx(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.vSize.x / 2));
	m_tRect.top = LONG(m_tInfo.vPos.y - (m_tInfo.vSize.y / 2));
	m_tRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.vSize.x / 2));
	m_tRect.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vSize.y / 2));
}