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

	const bool& Get_Evasive() const { return m_bEvasive; }
	const bool& Get_Start() const { return m_bStart; }
	const bool& Get_End() const { return m_bEnd; }

	void Set_End() { m_bEnd = true; }

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
	D3DXVECTOR3 m_vStart;

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;

	bool		m_bEvasive;
	float		m_fEvaAngle;

	bool		m_bStart;
	bool		m_bEnd;
};

#endif