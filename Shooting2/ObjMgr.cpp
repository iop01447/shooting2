#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"


CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj * _pObj)
{
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj * _pObj, int _iCX, int _iCY)
{
	m_listObj[_eID].emplace_back(_pObj);
	//m_listObj[_eID].back()->Set_Size(_iCX, _iCY);
	
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
 			int iEvent = (*iter)->Update();
			if (m_listObj[i].empty())
				break;
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();
			if (m_listObj[i].empty())
				break;
		}
	}

	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET]);
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MOUSE], m_listObj[OBJID::BULLET]);
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::PLAYER], m_listObj[OBJID::GOLD]);
}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(_DC);
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

CObj* CObjMgr::Get_Target(CObj* _pObj, OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	//float	fDis = 0.f;

	//for (auto& pNode : m_listObj[_eID])
	//{
	//	if(pNode->Get_Dead())
	//		continue;

	//	float fX = abs(_pObj->Get_Info().fX - pNode->Get_Info().fX);
	//	float fY = abs(_pObj->Get_Info().fY - pNode->Get_Info().fY);
	//	float fDis2 = sqrtf(fX * fX + fY * fY);

	//	if (!pTarget || fDis > fDis2)
	//	{
	//		pTarget = pNode;
	//		fDis = fDis2;
	//	}
	//}
	return pTarget;
}

void CObjMgr::Delete_ID(OBJID::ID _eID)
{
	for (auto& pObj : m_listObj[_eID])
		Safe_Delete(pObj);

	m_listObj[_eID].clear();
}
