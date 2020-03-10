#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void KeyCheck();
	void Boundary_Check();

private:
	template <typename T>
	CObj* Create_Bullet(float _x, float _y, float _fAngle = 0.f)
	{
		CObj* pObj = CAbstractFactory<T>::Create(_x, _y, _fAngle);
		return pObj;
	}

private:
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4]; // P
	D3DXVECTOR3 m_vPosin;

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;
};

#endif